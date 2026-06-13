#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "CommonInputBaseTypes.h"

#include "Nexus/Input/NexusInputTypes.h"

#include "NexusInputContext.generated.h"

class UInputMappingContext;
class UNexusInputConfig;


/**
 * An alternate Input Mapping Context to apply for one device family. The manager
 * swaps to it on UCommonInputSubsystem::OnInputMethodChangedNative so a pad layout
 * can differ from KB&M without touching consumers. Falls back to the context's
 * default MappingContext when no per-device entry matches the live device.
 */
USTRUCT(BlueprintType)
struct NEXUS_API FNexusDeviceMappingContext
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Context")
	ECommonInputType Device = ECommonInputType::Gamepad;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Context")
	TObjectPtr<UInputMappingContext> MappingContext = nullptr;
};


/**
 * The unit the context stack pushes — a data asset describing one modal/overlay input
 * mode (Gameplay, Examine, Menu, Dialog, Cinematic, Vehicle). Carries its Input
 * Mapping Context(s), its tagged bindings (inline + shared configs), its place in the
 * stack, and whether it suppresses lower verbs. Authoring a mode is authoring one of
 * these and pushing it — no C++.
 */
UCLASS(BlueprintType)
class NEXUS_API UNexusInputContext : public UDataAsset
{
	GENERATED_BODY()

public:
	/** Identity of this context (Input.Context.*). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Context", meta = (Categories = "Input.Context"))
	FGameplayTag ContextTag;

	/** Higher sits on top of the stack and resolves verbs first. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Context")
	int32 Priority = 0;

	/**
	 * Modal contexts block every verb below them (their IMCs are suspended). An overlay
	 * (false) lets lower verbs through except those listed in SuppressedVerbsBelow.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Context")
	bool bModal = false;

	/**
	 * A UI mode (Menu / Dialog) hands its input mode to a Common UI activatable widget
	 * via GetDesiredInputConfig — the manager only suspends gameplay underneath and never
	 * calls SetInputMode. An in-world mode (Gameplay / Examine / Vehicle) is owned here.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Context")
	bool bIsUIContext = false;

	/**
	 * Verbs from lower contexts blocked while this one is active, even under an overlay.
	 * The input-mode gate — the home of today's scattered IsExamining() checks. A modal
	 * context suppresses everything below structurally; this list is for selective overlay
	 * gating.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Context", meta = (Categories = "Input"))
	FGameplayTagContainer SuppressedVerbsBelow;

	/** The default Input Mapping Context applied while this context is active and unsuppressed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Context|Mapping")
	TObjectPtr<UInputMappingContext> MappingContext = nullptr;

	/** Optional per-device overrides for MappingContext (auto-swapped on device change). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Context|Mapping")
	TArray<FNexusDeviceMappingContext> DeviceMappingContexts;

	/** Shared binding sets this context pulls in, merged ahead of the inline bindings. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Context|Bindings")
	TArray<TObjectPtr<UNexusInputConfig>> SharedConfigs;

	/** Bindings authored directly on this context. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Context|Bindings",
		meta = (TitleProperty = "InputTag"))
	TArray<FNexusTaggedInputAction> Bindings;

public:
	/** Every binding this context contributes (shared configs first, then inline), in priority order. */
	void GatherBindings(TArray<FNexusTaggedInputAction>& OutBindings) const;

	/** The Input Mapping Context to apply for Device, falling back to the default MappingContext. */
	UInputMappingContext* ResolveMappingContext(ECommonInputType Device) const;

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif
};
