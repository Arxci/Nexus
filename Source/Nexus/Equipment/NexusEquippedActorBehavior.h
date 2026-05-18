#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "GameplayTagContainer.h"

#include "NexusEquippedActorBehavior.generated.h"

class ANexusEquippedActor;


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
 * Animation routing does NOT pass through behaviors — montages live on the
 * equippable fragment's Actions map and resolve through UNexusAssemblyComponent
 * so attachment overrides apply uniformly. Behaviors own non-animation runtime
 * state (chamber-round visual, magazine swap, future flashlight cone, etc.).
 */
UCLASS(Abstract, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class NEXUS_API UNexusEquippedActorBehavior : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void OnInstalled(ANexusEquippedActor* InEquippedActor) { EquippedActor = InEquippedActor; }
	virtual void OnUninstalled() {}
	virtual void ApplyViewpoint(bool bIsFirstPerson) {}

protected:
	UPROPERTY(Transient, BlueprintReadOnly, Category = "Equipped")
	TObjectPtr<ANexusEquippedActor> EquippedActor;
};