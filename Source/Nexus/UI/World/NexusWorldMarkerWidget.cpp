// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusWorldMarkerWidget.h"

#include "NexusWorldMarkerWidget.h"

void UNexusWorldMarkerWidget::SetContext(USceneComponent* InAnchor, AActor* InContextActor)
{
	Anchor = InAnchor;

	// If no explicit context actor given, infer from the anchor's owner.
	ContextActor = InContextActor
		? InContextActor
		: (InAnchor ? InAnchor->GetOwner() : nullptr);

	OnContextChanged.Broadcast();
	K2_OnContextChanged();
}

FVector UNexusWorldMarkerWidget::GetWorldLocation() const
{
	if (const USceneComponent* AnchorPtr = Anchor.Get())
	{
		return AnchorPtr->GetComponentLocation();
	}
	if (const AActor* ActorPtr = ContextActor.Get())
	{
		return ActorPtr->GetActorLocation();
	}
	return FVector::ZeroVector;
}

void UNexusWorldMarkerWidget::AddStateTag(FGameplayTag Tag)
{
	if (!Tag.IsValid() || StateTags.HasTagExact(Tag)) return;

	StateTags.AddTag(Tag);
	HandleStateTagChanged(Tag, /*bAdded=*/true);
}

void UNexusWorldMarkerWidget::RemoveStateTag(FGameplayTag Tag)
{
	if (!Tag.IsValid() || !StateTags.HasTagExact(Tag)) return;

	StateTags.RemoveTag(Tag);
	HandleStateTagChanged(Tag, /*bAdded=*/false);
}

void UNexusWorldMarkerWidget::SetStateTags(const FGameplayTagContainer& NewTags)
{
	// Compute deltas so listeners see per-tag add/remove, not a wholesale replace.
	FGameplayTagContainer Added;
	for (const FGameplayTag& Tag : NewTags)
	{
		if (!StateTags.HasTagExact(Tag)) Added.AddTag(Tag);
	}

	FGameplayTagContainer Removed;
	for (const FGameplayTag& Tag : StateTags)
	{
		if (!NewTags.HasTagExact(Tag)) Removed.AddTag(Tag);
	}

	StateTags = NewTags;

	for (const FGameplayTag& Tag : Removed) HandleStateTagChanged(Tag, false);
	for (const FGameplayTag& Tag : Added)   HandleStateTagChanged(Tag, true);
}

void UNexusWorldMarkerWidget::HandleStateTagChanged(FGameplayTag Tag, bool bAdded)
{
	OnStateTagChanged.Broadcast(Tag, bAdded);
	K2_OnStateTagChanged(Tag, bAdded);
}