#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "Nexus/Equipment/Attachments/NexusAssemblyComponent.h"

#include "NexusEquippedActor.generated.h"

class UAnimMontage;
class UAnimSequence;
class UNexusItemInstance;
class USkeletalMeshComponent;


UCLASS(Blueprintable)
class NEXUS_API ANexusEquippedActor : public AActor
{
    GENERATED_BODY()

public:
    ANexusEquippedActor();

    virtual void InitializeFromInstance(UNexusItemInstance* Instance);

    UFUNCTION(BlueprintPure, Category = "Equipped")
    UNexusItemInstance* GetSourceInstance() const { return SourceInstance; }

    UFUNCTION(BlueprintPure, Category = "Equipped")
    USkeletalMeshComponent* GetMesh() const { return Mesh; }

    UFUNCTION(BlueprintPure, Category = "Equipped")
    FTransform GetSocketTransform(const FName SocketName) const;

    UFUNCTION(BlueprintCallable, Category = "Equipped")
    void SetEquippedVisibility(bool bNewVisible);

    UFUNCTION(BlueprintPure, Category = "Equipped")
    bool IsEquippedVisible() const { return bVisible; }

    UFUNCTION(BlueprintCallable, Category = "Equipped")
    void ApplyOwnerViewpointRendering();

    void ApplyViewpointToMesh(USkeletalMeshComponent* TargetMesh) const;

    UFUNCTION(BlueprintPure, Category = "Equipped")
    bool IsRenderedFirstPerson() const { return bIsFirstPersonView; }


    /**
     * Resolve the effective arms-side montage for ActionTag, walking attachment
     * overrides first (deeper wins) and falling back to the equippable
     * fragment's authored Actions map. Returns null if neither path supplies
     * an arms montage for that action.
     *
     * Callers play the result on the player's first-person/character mesh —
     * see UNexusEquipmentComponent::PlayMontageOnOwner and the weapon abilities.
     */
    UFUNCTION(BlueprintPure, Category = "Equipped|Anim")
    UAnimMontage* GetEffectiveArmsMontage(FGameplayTag ActionTag) const;

    /**
     * Resolve the effective item-mesh montage for ActionTag (the gun's slide /
     * bolt / magazine animation), with the same override-then-fallback walk as
     * the arms variant. Returns null when an action has no item-side animation.
     */
    UFUNCTION(BlueprintPure, Category = "Equipped|Anim")
    UAnimMontage* GetEffectiveItemMontage(FGameplayTag ActionTag) const;

    /**
     * Play the item-mesh montage for ActionTag on this actor's own mesh.
     * Called by UNexusAnimNotify_EquipmentAction at the authored notify frame on
     * the arms montage, so the item animates in lockstep with the arms.
     * Returns the montage that was played, or null if none was resolved.
     */
    UFUNCTION(BlueprintCallable, Category = "Equipped|Anim")
    UAnimMontage* PlayItemActionMontage(FGameplayTag ActionTag);

    UFUNCTION(BlueprintPure, Category = "Equipped|Stats")
    float GetEffectiveStat(FGameplayTag StatTag, float Default = 0.0f) const;

    UFUNCTION(BlueprintPure, Category = "Equipped|Stats")
    FResolvedItemStats GetResolvedStats() const;

    UFUNCTION(BlueprintPure, Category = "Equipped|Assembly")
    UNexusAssemblyComponent* GetAssembly() const { return Assembly; }

public:
    /**
     * Equipped-mesh idle/run poses cached from FNexusFragment_Equippable::Animations
     * at InitializeFromInstance. The mesh's AnimBP samples these — kept on the
     * actor so AnimBP graphs don't have to walk fragment data each frame.
     *
     * Action montages (Holster/Unholster/Fire/Reload/etc.) are NOT cached here;
     * they're resolved on demand via GetEffectiveArmsMontage / GetEffectiveItemMontage
     * so attachment overrides apply correctly.
     */
    UPROPERTY(BlueprintReadOnly, Category = "Equipment|Anims")
    TObjectPtr<UAnimSequence> IdlePose;

    UPROPERTY(BlueprintReadOnly, Category = "Equipment|Anims")
    TObjectPtr<UAnimSequence> IdleLoop;

    UPROPERTY(BlueprintReadOnly, Category = "Equipment|Anims")
    TObjectPtr<UAnimSequence> RunLoop;

protected:
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipped")
    TObjectPtr<USkeletalMeshComponent> Mesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipped")
    TObjectPtr<UNexusAssemblyComponent> Assembly;

    UPROPERTY(Transient, BlueprintReadOnly, Category = "Equipped")
    TObjectPtr<UNexusItemInstance> SourceInstance;

    UPROPERTY(Transient)
    bool bVisible = true;

    UPROPERTY(Transient)
    bool bIsFirstPersonView = false;

    UFUNCTION(BlueprintImplementableEvent, Category = "Equipped",
        meta = (DisplayName = "On Initialized From Instance"))
    void K2_OnInitializedFromInstance();

    UFUNCTION(BlueprintImplementableEvent, Category = "Equipped",
        meta = (DisplayName = "On Equipped Visibility Changed"))
    void K2_OnEquippedVisibilityChanged(bool bNewVisible);

    UFUNCTION(BlueprintImplementableEvent, Category = "Equipped",
        meta = (DisplayName = "On Owner Viewpoint Applied"))
    void K2_OnOwnerViewpointApplied(bool bIsFirstPerson);
};