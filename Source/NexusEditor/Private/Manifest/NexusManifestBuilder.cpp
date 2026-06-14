#include "Manifest/NexusManifestBuilder.h"

#include "Editor.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/WorldSettings.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "Misc/PackageName.h"
#include "UObject/Package.h"
#include "UObject/SoftObjectPath.h"

#include "Nexus/Levels/NexusLevelManifest.h"
#include "Nexus/Levels/NexusWorldSettings.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"

#include "Settings/NexusEditorSettings.h"

#define LOCTEXT_NAMESPACE "NexusManifestBuilder"

namespace
{
	/** Make a level name path-safe for an asset name (the naming validator flags the rest). */
	FString SanitizeName(const FString& In)
	{
		FString Out;
		Out.Reserve(In.Len());
		for (const TCHAR Ch : In)
		{
			Out.AppendChar((FChar::IsAlnum(Ch) || Ch == TEXT('_')) ? Ch : TEXT('_'));
		}
		return Out.IsEmpty() ? TEXT("Level") : Out;
	}

	/**
	 * True when an existing manifest array (TSoftObjectPtr entries) already holds exactly
	 * NewSet, compared by soft path so load state doesn't matter.
	 */
	template <typename TArrayType, typename TElem>
	bool MatchesSet(const TArrayType& Existing, const TSet<TElem*>& NewSet)
	{
		if (Existing.Num() != NewSet.Num())
		{
			return false;
		}
		TSet<FSoftObjectPath> NewPaths;
		NewPaths.Reserve(NewSet.Num());
		for (TElem* Obj : NewSet)
		{
			if (Obj) { NewPaths.Add(FSoftObjectPath(Obj)); }
		}
		for (const auto& Entry : Existing)
		{
			if (!NewPaths.Contains(Entry.ToSoftObjectPath()))
			{
				return false;
			}
		}
		return true;
	}

	UNexusLevelManifest* CreateManifestAsset(const FString& AssetName)
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		FString OutPackageName, OutAssetName;
		AssetTools.CreateUniqueAssetName(UNexusEditorSettings::Get().ManifestFolder / AssetName, FString(), OutPackageName, OutAssetName);

		UPackage* Package = CreatePackage(*OutPackageName);
		if (!Package) { return nullptr; }

		UNexusLevelManifest* Manifest =
			NewObject<UNexusLevelManifest>(Package, FName(*OutAssetName), RF_Public | RF_Standalone | RF_Transactional);
		if (Manifest)
		{
			FAssetRegistryModule::AssetCreated(Manifest);
			Package->MarkPackageDirty();
		}
		return Manifest;
	}
}

UNexusLevelManifest* FNexusManifestBuilder::BuildFromCurrentLevel(FString& OutMessage)
{
	UWorld* World = GEditor ? GEditor->GetEditorWorldContext().World() : nullptr;
	if (!World)
	{
		OutMessage = TEXT("No active editor level.");
		return nullptr;
	}

	// Harvest every item / attachment definition referenced by a placed actor (or its
	// components). FReferenceFinder walks properties regardless of access level, so it
	// catches a pickup's protected Definition. Hard references only — soft refs aren't
	// followed, but placed pickups/spawners use hard refs.
	TSet<UNexusItemDefinition*> Items;
	TSet<UNexusAttachmentDefinition*> Attachments;

	for (TActorIterator<AActor> It(World); It; ++It)
	{
		AActor* Actor = *It;
		if (!Actor) { continue; }

		TArray<UObject*> Found;
		FReferenceFinder Finder(Found, nullptr, false, false, true, false);
		Finder.FindReferences(Actor);

		TInlineComponentArray<UActorComponent*> Components(Actor);
		for (UActorComponent* Component : Components)
		{
			if (Component) { Finder.FindReferences(Component); }
		}

		for (UObject* Object : Found)
		{
			if (UNexusItemDefinition* Item = Cast<UNexusItemDefinition>(Object))
			{
				Items.Add(Item);
			}
			else if (UNexusAttachmentDefinition* Attachment = Cast<UNexusAttachmentDefinition>(Object))
			{
				Attachments.Add(Attachment);
			}
		}
	}

	// Target the manifest the level already points at, or make + wire a new one.
	ANexusWorldSettings* WorldSettings = Cast<ANexusWorldSettings>(World->GetWorldSettings());
	UNexusLevelManifest* Manifest = WorldSettings ? ToRawPtr(WorldSettings->LevelManifest) : nullptr;
	bool bCreated = false;

	if (!Manifest)
	{
		const FString LevelName = SanitizeName(FPackageName::GetShortName(World->GetOutermost()->GetName()));
		Manifest = CreateManifestAsset(FString(TEXT("LM_")) + LevelName);
		if (!Manifest)
		{
			OutMessage = TEXT("Could not create a manifest asset.");
			return nullptr;
		}
		bCreated = true;

		if (WorldSettings)
		{
			WorldSettings->LevelManifest = Manifest;
			WorldSettings->MarkPackageDirty(); // dirties the level — save it too
		}
	}

	// Skip needless dirtying when the level's content already matches the manifest.
	if (!bCreated && MatchesSet(Manifest->Items, Items) && MatchesSet(Manifest->Attachments, Attachments))
	{
		OutMessage = FString::Printf(
			TEXT("Manifest '%s' is already up to date (%d item(s), %d attachment(s))."),
			*Manifest->GetName(), Items.Num(), Attachments.Num());
		return Manifest;
	}

	Manifest->Items.Reset();
	Manifest->Attachments.Reset();
	for (UNexusItemDefinition* Item : Items) { Manifest->Items.Add(Item); }
	for (UNexusAttachmentDefinition* Attachment : Attachments) { Manifest->Attachments.Add(Attachment); }
	Manifest->MarkPackageDirty();

	const FString AssignNote = (bCreated && !WorldSettings)
		? TEXT(" (couldn't auto-assign — this level isn't using ANexusWorldSettings)")
		: (bCreated ? TEXT(" and assigned it to the level's World Settings (save the level too)") : TEXT(""));

	OutMessage = FString::Printf(TEXT("%s '%s' with %d item(s) and %d attachment(s)%s. Save it in the Content Browser."),
		bCreated ? TEXT("Created") : TEXT("Updated"),
		*Manifest->GetName(), Items.Num(), Attachments.Num(), *AssignNote);
	return Manifest;
}

#undef LOCTEXT_NAMESPACE
