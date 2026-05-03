#include "NexusWorldMarkerWidget.h"

void UNexusWorldMarkerWidget::SetContext(USceneComponent* InAnchor, AActor* InContextActor)
{
	Anchor = InAnchor;
	
	ContextActor = InContextActor
		? InContextActor
		: (InAnchor ? InAnchor->GetOwner() : nullptr);

	OnContextChanged.Broadcast();
	K2_OnContextChanged();
}

//Utility
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

//State
void UNexusWorldMarkerWidget::AddStateTag(const FGameplayTag Tag)
{
	if (!Tag.IsValid() || StateTags.HasTagExact(Tag)) return;

	StateTags.AddTag(Tag);
	HandleStateTagChanged(Tag, true);
}

void UNexusWorldMarkerWidget::RemoveStateTag(const FGameplayTag Tag)
{
	if (!Tag.IsValid() || !StateTags.HasTagExact(Tag)) return;

	StateTags.RemoveTag(Tag);
	HandleStateTagChanged(Tag, false);
}

void UNexusWorldMarkerWidget::SetStateTags(const FGameplayTagContainer& NewTags)
{
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

void UNexusWorldMarkerWidget::HandleStateTagChanged(const FGameplayTag Tag, const bool bAdded)
{
	OnStateTagChanged.Broadcast(Tag, bAdded);
	K2_OnStateTagChanged(Tag, bAdded);
}