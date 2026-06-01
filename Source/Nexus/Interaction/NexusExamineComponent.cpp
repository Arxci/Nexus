#include "NexusExamineComponent.h"

#include "Camera/CameraComponent.h"

#include "Components/StaticMeshComponent.h"

#include "Engine/StaticMesh.h"

#include "Nexus/AbilitySystem/NexusAbilitySystemComponent.h"
#include "Nexus/Crafting/NexusItemCombinationSubsystem.h"
#include "Nexus/Game/NexusWorldStateSubsystem.h"
#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/NexusGameplayTags.h"

UNexusExamineComponent::UNexusExamineComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UNexusAbilitySystemComponent* UNexusExamineComponent::GetASC() const
{
	AActor* Owner = GetOwner();
	return Owner ? Owner->FindComponentByClass<UNexusAbilitySystemComponent>() : nullptr;
}

UCameraComponent* UNexusExamineComponent::GetViewCamera() const
{
	AActor* Owner = GetOwner();
	return Owner ? Owner->FindComponentByClass<UCameraComponent>() : nullptr;
}

void UNexusExamineComponent::BeginExamine(const FNexusExamineData& Data)
{
	if (bExamining) return;

	UCameraComponent* Camera = GetViewCamera();
	if (!Camera || !Data.Mesh) return; // need a view + something to show

	AActor* Owner = GetOwner();
	if (!Owner) return;

	CurrentData = Data;
	bExamining = true;
	MeshRotation = FRotator::ZeroRotator;
	RevealTriggered.Init(false, CurrentData.Reveals.Num());

	// Pose the mesh in front of the camera (deferred add → manual attach, the same
	// pattern the interactable component uses to spawn its world-marker widget).
	UActorComponent* NewComp = Owner->AddComponentByClass(
		UStaticMeshComponent::StaticClass(), true, FTransform::Identity, true);
	ExamineMesh = Cast<UStaticMeshComponent>(NewComp);
	if (ExamineMesh)
	{
		ExamineMesh->AttachToComponent(Camera, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		ExamineMesh->SetStaticMesh(CurrentData.Mesh);
		ExamineMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ExamineMesh->SetCastShadow(false);
		ExamineMesh->SetRelativeLocation(FVector(CurrentData.ViewDistance, 0.f, 0.f) + CurrentData.ViewOffset);
		ExamineMesh->SetRelativeRotation(MeshRotation);
		Owner->FinishAddComponent(ExamineMesh, true, FTransform::Identity);
	}

	// Own the Examining state tag so other abilities can gate off it, and cancel
	// any active ones (a held weapon's fire, an active aim) as we take over.
	if (UNexusAbilitySystemComponent* ASC = GetASC())
	{
		ASC->AddLooseGameplayTag(NexusGameplayTags::Character_State_Examining);
		ASC->DeactivateAllAbilities();
	}

	OnExamineStarted.Broadcast();
}

void UNexusExamineComponent::EndExamine()
{
	if (!bExamining) return;
	bExamining = false;

	if (ExamineMesh)
	{
		ExamineMesh->DestroyComponent();
		ExamineMesh = nullptr;
	}

	if (UNexusAbilitySystemComponent* ASC = GetASC())
	{
		ASC->RemoveLooseGameplayTag(NexusGameplayTags::Character_State_Examining);
	}

	CurrentData = FNexusExamineData();
	RevealTriggered.Reset();

	OnExamineEnded.Broadcast();
}

void UNexusExamineComponent::AddRotationInput(FVector2D LookInput)
{
	if (!bExamining || !ExamineMesh) return;

	// Drag-to-rotate: yaw from horizontal look, pitch from vertical.
	MeshRotation.Yaw   += LookInput.X * CurrentData.RotationSpeed;
	MeshRotation.Pitch += LookInput.Y * CurrentData.RotationSpeed;
	ExamineMesh->SetRelativeRotation(MeshRotation);

	CheckReveals();
}

void UNexusExamineComponent::CheckReveals()
{
	for (int32 i = 0; i < CurrentData.Reveals.Num(); ++i)
	{
		if (RevealTriggered.IsValidIndex(i) && RevealTriggered[i]) continue;

		const FNexusExamineReveal& Reveal = CurrentData.Reveals[i];
		const float AngleDeg = FMath::RadiansToDegrees(
			MeshRotation.Quaternion().AngularDistance(Reveal.RevealAngle.Quaternion()));
		if (AngleDeg > Reveal.AngleTolerance) continue;

		if (RevealTriggered.IsValidIndex(i))
		{
			RevealTriggered[i] = true;
		}

		if (Reveal.SetWorldStateKey.IsValid())
		{
			if (UNexusWorldStateSubsystem* WorldState = UNexusWorldStateSubsystem::Get(this))
			{
				WorldState->SetValue(Reveal.SetWorldStateKey, 1);
			}
		}

		OnExamineRevealed.Broadcast(Reveal.RevealText);
	}
}

bool UNexusExamineComponent::TryCombine(int32 RecipeIndex)
{
	if (!bExamining || !CurrentData.CombineRecipes.IsValidIndex(RecipeIndex)) return false;

	UNexusCombinationRecipe* Recipe = CurrentData.CombineRecipes[RecipeIndex];
	if (!Recipe) return false;

	AActor* Owner = GetOwner();
	UNexusInventoryComponent* Inventory = Owner ? Owner->FindComponentByClass<UNexusInventoryComponent>() : nullptr;
	if (!Inventory) return false;

	UNexusItemCombinationSubsystem* Combination = UNexusItemCombinationSubsystem::Get(this);
	if (!Combination) return false;

	// Interaction only REQUESTS the combine; the subsystem owns the recipe data and
	// the inventory mutation (consume inputs + give output through the public API).
	return Combination->Craft(Inventory, Recipe);
}

void UNexusExamineComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (bExamining)
	{
		EndExamine();
	}
	Super::EndPlay(EndPlayReason);
}
