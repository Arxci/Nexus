#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "GameplayTagContainer.h"

#include "NexusEquippedActorBehavior.generated.h"

class ANexusEquippedActor;
class UAnimMontage;


/**
 * Base for actor-side behavior components installed on ANexusEquippedActor by
 * fragments. Each behavior carries the per-equipped-actor state and logic for
 * one item facet (weapon, future flashlight, future radio), so the equipped
 * actor stays a generic shell — new equipment categories ship as data assets
 * (a new fragment) plus a behavior component, no actor subclassing required.
 *
 * Behaviors are added in FNexusItemFragment::OnInstall and removed in
 * OnUninstall. Override OnInstalled / OnUninstalled here to wire delegates and
 * spawn child components after the parent actor exists.
 *
 * GetActionMontage lets the actor's generic PlayActionMontage path query each
 * installed behavior for an action montage without knowing about specific
 * fragment types.
 */
UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NEXUS_API UNexusEquippedActorBehavior : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Called after the behavior has been added & registered on the equipped actor. */
	virtual void OnInstalled(ANexusEquippedActor* InEquippedActor) { EquippedActor = InEquippedActor; }

	/** Called before the behavior is removed (manual uninstall, EndPlay). */
	virtual void OnUninstalled() {}

	/**
	 * Return an action montage for ActionTag, or nullptr if this behavior
	 * doesn't service that tag. Walked by the actor as a fallback after the
	 * weapon assembly's attachment-override resolution misses.
	 */
	virtual UAnimMontage* GetActionMontage(FGameplayTag ActionTag) const { return nullptr; }

	/**
	 * Apply the parent actor's resolved viewpoint state (cast-shadow,
	 * first-person primitive type) to whatever child meshes this behavior
	 * owns. Called by ANexusEquippedActor::ApplyOwnerViewpointRendering after
	 * the actor's main mesh and assembly attachments have been updated.
	 */
	virtual void ApplyViewpoint(bool bIsFirstPerson) {}

protected:
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Equipped")
	TObjectPtr<ANexusEquippedActor> EquippedActor;
};