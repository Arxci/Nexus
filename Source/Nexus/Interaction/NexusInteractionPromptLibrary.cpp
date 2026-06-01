#include "NexusInteractionPromptLibrary.h"

#include "Nexus/NexusGameplayTags.h"

#define LOCTEXT_NAMESPACE "NexusInteraction"

FText UNexusInteractionPromptLibrary::GetVerbText(FGameplayTag Verb)
{
	using namespace NexusGameplayTags;

	if (Verb == Interaction_Verb_PickUp)  return LOCTEXT("Verb_PickUp",  "Take");
	if (Verb == Interaction_Verb_Open)    return LOCTEXT("Verb_Open",    "Open");
	if (Verb == Interaction_Verb_Close)   return LOCTEXT("Verb_Close",   "Close");
	if (Verb == Interaction_Verb_Use)     return LOCTEXT("Verb_Use",     "Use");
	if (Verb == Interaction_Verb_Unlock)  return LOCTEXT("Verb_Unlock",  "Unlock");
	if (Verb == Interaction_Verb_Read)    return LOCTEXT("Verb_Read",    "Read");
	if (Verb == Interaction_Verb_Search)  return LOCTEXT("Verb_Search",  "Search");
	if (Verb == Interaction_Verb_Examine) return LOCTEXT("Verb_Examine", "Examine");
	if (Verb == Interaction_Verb_Talk)    return LOCTEXT("Verb_Talk",     "Talk");
	if (Verb == Interaction_Verb_Finisher) return LOCTEXT("Verb_Finisher", "Finish");

	return FText::GetEmpty();
}

FText UNexusInteractionPromptLibrary::GetEntryPrompt(const FNexusResolvedInteraction& Interaction)
{
	if (!Interaction.Prompt.IsEmpty()) return Interaction.Prompt;
	return GetVerbText(Interaction.Verb);
}

FText UNexusInteractionPromptLibrary::ResolvePrompt(const TArray<FNexusResolvedInteraction>& Interactions)
{
	const FNexusResolvedInteraction* BestEnabled = nullptr;
	const FNexusResolvedInteraction* FirstGated = nullptr;

	for (const FNexusResolvedInteraction& Entry : Interactions)
	{
		if (Entry.bEnabled)
		{
			// Prefer a Primary verb; otherwise take the first enabled.
			if (!BestEnabled ||
				(static_cast<uint8>(Entry.Slot) < static_cast<uint8>(BestEnabled->Slot)))
			{
				BestEnabled = &Entry;
			}
		}
		else if (!FirstGated && !Entry.FailReason.IsEmpty())
		{
			FirstGated = &Entry;
		}
	}

	if (BestEnabled) return GetEntryPrompt(*BestEnabled);
	if (FirstGated)  return FirstGated->FailReason;
	return FText::GetEmpty();
}

#undef LOCTEXT_NAMESPACE
