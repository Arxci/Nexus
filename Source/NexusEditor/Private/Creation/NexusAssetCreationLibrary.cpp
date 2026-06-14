#include "Creation/NexusAssetCreationLibrary.h"

#include "Shared/NexusEditorUtils.h"

#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "GameplayTagsManager.h"
#include "GameplayTagsEditorModule.h"
#include "Misc/PackageName.h"
#include "StructUtils/InstancedStruct.h"
#include "UObject/Package.h"

#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemFragment.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Inventory/Fragments/Equippable/NexusFragment_Equippable.h"
#include "Nexus/Inventory/Fragments/Equippable/NexusAttachmentTypes.h"
#include "Nexus/Weapon/Fragments/NexusFragment_Weapon.h"
#include "Nexus/Inventory/Fragments/Consumable/NexusFragment_Consumable.h"
#include "Nexus/Inventory/Fragments/Stackable/NexusFragment_Stackable.h"
#include "Nexus/Inventory/Fragments/Treasure/NexusFragment_Treasure.h"
#include "Nexus/Inventory/Fragments/KeyItem/NexusFragment_KeyItem.h"
#include "Nexus/Inventory/Fragments/Charm/NexusFragment_Charm.h"
#include "Nexus/Crafting/NexusCombinationRecipe.h"
#include "Nexus/Levels/NexusLevelManifest.h"
#include "Nexus/Equipment/NexusEquipmentLoadout.h"

#define LOCTEXT_NAMESPACE "NexusAssetCreation"

namespace
{
	/** Create an empty asset of type T at a uniquified package path. Null + OutError on failure. */
	template <typename T>
	T* StampAsset(const FString& PackagePath, const FString& DesiredName, FText& OutError)
	{
		FString Folder = PackagePath;
		Folder.RemoveFromEnd(TEXT("/"));
		if (Folder.IsEmpty())            { Folder = TEXT("/Game"); }
		if (!Folder.StartsWith(TEXT("/"))) { Folder = TEXT("/") + Folder; }

		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		FString OutPackageName, OutAssetName;
		AssetTools.CreateUniqueAssetName(Folder / DesiredName, FString(), OutPackageName, OutAssetName);

		UPackage* Package = CreatePackage(*OutPackageName);
		if (!Package)
		{
			OutError = FText::Format(LOCTEXT("PkgFail", "Could not create a package at {0}."), FText::FromString(OutPackageName));
			return nullptr;
		}

		T* Asset = NewObject<T>(Package, FName(*OutAssetName), RF_Public | RF_Standalone | RF_Transactional);
		if (!Asset)
		{
			OutError = LOCTEXT("ObjFail", "Could not create the asset object.");
			return nullptr;
		}

		FAssetRegistryModule::AssetCreated(Asset);
		Package->MarkPackageDirty();
		return Asset;
	}

	/** Append a default-constructed fragment of type FragmentT to the item. */
	template <typename FragmentT>
	void AddDefaultFragment(UNexusItemDefinition* Item)
	{
		TInstancedStruct<FNexusItemFragment> Frag;
		Frag.InitializeAs<FragmentT>();
		Item->Fragments.Add(MoveTemp(Frag));
	}

	/** The Attachment.Slot.* tag matching an Attachment.Type.* tag (same leaf), or invalid. */
	FGameplayTag SlotTagForType(const FGameplayTag& TypeTag)
	{
		FString Path = TypeTag.ToString();
		Path.ReplaceInline(TEXT(".Type."), TEXT(".Slot."));
		return FGameplayTag::RequestGameplayTag(FName(*Path), /*ErrorIfNotFound=*/ false);
	}
}

FText FNexusAssetCreation::TemplateLabel(ENexusItemTemplate Template)
{
	switch (Template)
	{
	case ENexusItemTemplate::RangedWeapon: return LOCTEXT("RangedWeapon", "Ranged Weapon");
	case ENexusItemTemplate::MeleeWeapon:  return LOCTEXT("MeleeWeapon", "Melee Weapon");
	case ENexusItemTemplate::Consumable:   return LOCTEXT("Consumable", "Consumable");
	case ENexusItemTemplate::Ammo:         return LOCTEXT("Ammo", "Ammo");
	case ENexusItemTemplate::Treasure:     return LOCTEXT("Treasure", "Treasure");
	case ENexusItemTemplate::KeyItem:      return LOCTEXT("KeyItem", "Key Item");
	case ENexusItemTemplate::Charm:        return LOCTEXT("Charm", "Charm");
	default:                               return LOCTEXT("GenericItem", "Generic Item");
	}
}

FString FNexusAssetCreation::TemplateDefaultName(ENexusItemTemplate Template)
{
	switch (Template)
	{
	case ENexusItemTemplate::RangedWeapon: return TEXT("NewRangedWeapon");
	case ENexusItemTemplate::MeleeWeapon:  return TEXT("NewMeleeWeapon");
	case ENexusItemTemplate::Consumable:   return TEXT("NewConsumable");
	case ENexusItemTemplate::Ammo:         return TEXT("NewAmmo");
	case ENexusItemTemplate::Treasure:     return TEXT("NewTreasure");
	case ENexusItemTemplate::KeyItem:      return TEXT("NewKeyItem");
	case ENexusItemTemplate::Charm:        return TEXT("NewCharm");
	default:                               return TEXT("NewItem");
	}
}

UNexusItemDefinition* FNexusAssetCreation::CreateItem(
	ENexusItemTemplate Template, const FString& PackagePath, const FString& DesiredName, FText& OutError)
{
	const FString Name = DesiredName.IsEmpty() ? TemplateDefaultName(Template) : DesiredName;

	UNexusItemDefinition* Item = StampAsset<UNexusItemDefinition>(PackagePath, Name, OutError);
	if (!Item)
	{
		return nullptr;
	}

	using namespace NexusGameplayTags;

	switch (Template)
	{
	case ENexusItemTemplate::RangedWeapon:
	case ENexusItemTemplate::MeleeWeapon:
	{
		Item->CategoryTags.AddTag(Item_Category_Weapon);
		Item->GridSize = FIntPoint(1, 2);

		// Equippable fragment: goes in the Primary slot and exposes a standard pistol-class
		// attachment slot set, each pre-wired to accept its matching Attachment.Type.* tag —
		// the exact wiring that's tedious to author by hand for every gun.
		FNexusFragment_Equippable Equippable;
		Equippable.PreferredSlot = Equipment_Slot_Primary;
		Equippable.AllowedSlots.AddTag(Equipment_Slot_Primary);

		auto AddSlot = [&Equippable](const FGameplayTag& SlotId, const FGameplayTag& AcceptType)
		{
			FAssemblySlotDefinition Slot;
			Slot.SlotID = SlotId;
			Slot.AcceptedTags.AddTag(AcceptType);
			Equippable.Slots.Add(Slot);
		};
		AddSlot(Attachment_Slot_Sight,    Attachment_Type_Sight);
		AddSlot(Attachment_Slot_Barrel,   Attachment_Type_Barrel);
		AddSlot(Attachment_Slot_Magazine, Attachment_Type_Magazine);

		TInstancedStruct<FNexusItemFragment> EquippableFrag;
		EquippableFrag.InitializeAs<FNexusFragment_Equippable>(Equippable);
		Item->Fragments.Add(MoveTemp(EquippableFrag));

		// Weapon fragment with the capability flags set for the chosen template; the spec
		// structs carry sensible defaults (RPM 300, mag 12, etc.) for immediate testing.
		FNexusFragment_Weapon Weapon;
		Weapon.bHasRanged = (Template == ENexusItemTemplate::RangedWeapon);
		Weapon.bHasMelee  = (Template == ENexusItemTemplate::MeleeWeapon);

		TInstancedStruct<FNexusItemFragment> WeaponFrag;
		WeaponFrag.InitializeAs<FNexusFragment_Weapon>(Weapon);
		Item->Fragments.Add(MoveTemp(WeaponFrag));
		break;
	}
	case ENexusItemTemplate::Consumable:
		Item->CategoryTags.AddTag(Item_Category_Consumable);
		AddDefaultFragment<FNexusFragment_Consumable>(Item);
		AddDefaultFragment<FNexusFragment_Stackable>(Item);
		break;

	case ENexusItemTemplate::Ammo:
		Item->CategoryTags.AddTag(Item_Category_Ammo);
		AddDefaultFragment<FNexusFragment_Stackable>(Item);
		break;

	case ENexusItemTemplate::Treasure:
		Item->CategoryTags.AddTag(Item_Category_Treasure);
		AddDefaultFragment<FNexusFragment_Treasure>(Item);
		break;

	case ENexusItemTemplate::KeyItem:
		Item->CategoryTags.AddTag(Item_Category_Key);
		AddDefaultFragment<FNexusFragment_KeyItem>(Item);
		break;

	case ENexusItemTemplate::Charm:
		Item->CategoryTags.AddTag(Item_Category_Charm);
		AddDefaultFragment<FNexusFragment_Charm>(Item);
		break;

	case ENexusItemTemplate::Generic:
	default:
		break;
	}

	return Item;
}

UNexusAttachmentDefinition* FNexusAssetCreation::CreateAttachment(
	const FGameplayTag& TypeTag, const FString& PackagePath, const FString& DesiredName, FText& OutError)
{
	const FString Name = DesiredName.IsEmpty() ? TEXT("NewAttachment") : DesiredName;

	UNexusAttachmentDefinition* Attachment = StampAsset<UNexusAttachmentDefinition>(PackagePath, Name, OutError);
	if (!Attachment)
	{
		return nullptr;
	}

	// Seed ProvidedTags with the chosen type so the attachment already fits any slot whose
	// AcceptedTags include it — i.e. it drops straight into a freshly stamped gun's slot.
	if (TypeTag.IsValid())
	{
		Attachment->ProvidedTags.AddTag(TypeTag);
	}
	return Attachment;
}

ENexusAttachResult FNexusAssetCreation::AssignOrCreateSlot(
	UNexusItemDefinition* Weapon, UNexusAttachmentDefinition* Attachment,
	const FGameplayTag& TypeTag, FString& OutSlotName)
{
	if (!Weapon || !Attachment)
	{
		return ENexusAttachResult::NoEquippable;
	}

	for (TInstancedStruct<FNexusItemFragment>& Frag : Weapon->Fragments)
	{
		if (!Frag.IsValid())
		{
			continue;
		}
		const UScriptStruct* Type = Frag.GetScriptStruct();
		if (!Type || !Type->IsChildOf(FNexusFragment_Equippable::StaticStruct()))
		{
			continue;
		}

		FNexusFragment_Equippable* Equippable = Frag.GetMutablePtr<FNexusFragment_Equippable>();
		if (!Equippable)
		{
			continue;
		}

		// Prefer an existing empty slot that accepts this type.
		bool bFoundMatchingSlot = false;
		for (FAssemblySlotDefinition& Slot : Equippable->Slots)
		{
			if (!Slot.AcceptedTags.HasTag(TypeTag))
			{
				continue;
			}
			bFoundMatchingSlot = true;
			if (Slot.DefaultAttachment.IsNull())
			{
				Slot.DefaultAttachment = Attachment;
				OutSlotName = NexusEditorUtil::TagLeaf(Slot.SlotID);
				Weapon->MarkPackageDirty();
				return ENexusAttachResult::Assigned;
			}
		}

		// No slot of this type at all → add one and fill it (the "press Trigger, get a Trigger slot" path).
		if (!bFoundMatchingSlot)
		{
			const FGameplayTag SlotTag = SlotTagForType(TypeTag);
			FAssemblySlotDefinition NewSlot;
			NewSlot.SlotID = SlotTag.IsValid() ? SlotTag : TypeTag;
			NewSlot.AcceptedTags.AddTag(TypeTag);
			NewSlot.DefaultAttachment = Attachment;
			Equippable->Slots.Add(NewSlot);
			OutSlotName = NexusEditorUtil::TagLeaf(NewSlot.SlotID);
			Weapon->MarkPackageDirty();
			return ENexusAttachResult::CreatedSlot;
		}

		// Matching slot(s) exist but all are filled.
		OutSlotName = NexusEditorUtil::TagLeaf(TypeTag);
		return ENexusAttachResult::AllFilled;
	}

	return ENexusAttachResult::NoEquippable;
}

FString FNexusAssetCreation::SubfolderForTemplate(ENexusItemTemplate Template)
{
	switch (Template)
	{
	case ENexusItemTemplate::RangedWeapon:
	case ENexusItemTemplate::MeleeWeapon:  return TEXT("Weapons");
	case ENexusItemTemplate::Consumable:   return TEXT("Consumables");
	case ENexusItemTemplate::Ammo:         return TEXT("Ammo");
	case ENexusItemTemplate::Treasure:     return TEXT("Treasures");
	case ENexusItemTemplate::KeyItem:      return TEXT("KeyItems");
	case ENexusItemTemplate::Charm:        return TEXT("Charms");
	default:                               return TEXT("Items");
	}
}

UObject* FNexusAssetCreation::DuplicateAsset(UObject* Source, const FString& PackagePath, FText& OutError)
{
	if (!Source)
	{
		OutError = LOCTEXT("DupNull", "Nothing to duplicate.");
		return nullptr;
	}

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	FString Folder = PackagePath;
	Folder.RemoveFromEnd(TEXT("/"));
	if (Folder.IsEmpty()) { Folder = TEXT("/Game"); }

	FString OutPackageName, OutAssetName;
	AssetTools.CreateUniqueAssetName(Folder / (Source->GetName() + TEXT("_Copy")), FString(), OutPackageName, OutAssetName);

	UObject* Copy = AssetTools.DuplicateAsset(OutAssetName, FPackageName::GetLongPackagePath(OutPackageName), Source);
	if (!Copy)
	{
		OutError = LOCTEXT("DupFail", "Duplication failed.");
	}
	return Copy;
}

FGameplayTag FNexusAssetCreation::DeriveAndAssignIdentityTag(UObject* Asset, FText& OutError)
{
	UNexusItemDefinition* Item = Cast<UNexusItemDefinition>(Asset);
	UNexusAttachmentDefinition* Attachment = Cast<UNexusAttachmentDefinition>(Asset);

	FString Root;
	FString Category;
	if (Item)
	{
		Root = TEXT("Item.Identity");
		for (const FGameplayTag& CategoryTag : Item->CategoryTags) { Category = NexusEditorUtil::TagLeaf(CategoryTag); break; }
	}
	else if (Attachment)
	{
		Root = TEXT("Attachment.Identity");
		for (const FGameplayTag& ProvidedTag : Attachment->ProvidedTags) { Category = NexusEditorUtil::TagLeaf(ProvidedTag); break; }
	}
	else
	{
		OutError = LOCTEXT("NotNexusAsset", "Auto-tag only works on Nexus items and attachments.");
		return FGameplayTag();
	}

	// Keep only tag-legal characters from the asset name (alphanumerics + underscore).
	FString Name;
	for (const TCHAR Ch : Asset->GetName())
	{
		if (FChar::IsAlnum(Ch) || Ch == TEXT('_')) { Name.AppendChar(Ch); }
	}
	if (Name.IsEmpty()) { Name = TEXT("Unnamed"); }

	const FString TagString = Category.IsEmpty()
		? FString::Printf(TEXT("%s.%s"), *Root, *Name)
		: FString::Printf(TEXT("%s.%s.%s"), *Root, *Category, *Name);

	IGameplayTagsEditorModule& TagEditor = FModuleManager::LoadModuleChecked<IGameplayTagsEditorModule>("GameplayTagsEditor");
	TagEditor.AddNewGameplayTagToINI(TagString);
	const FGameplayTag Tag = UGameplayTagsManager::Get().RequestGameplayTag(FName(*TagString), /*ErrorIfNotFound=*/ false);
	if (!Tag.IsValid())
	{
		OutError = FText::Format(LOCTEXT("TagRegFail", "Could not register tag {0}."), FText::FromString(TagString));
		return FGameplayTag();
	}

	if (Item)            { Item->IdentityTag = Tag; Item->MarkPackageDirty(); }
	else if (Attachment) { Attachment->IdentityTag = Tag; Attachment->MarkPackageDirty(); }
	return Tag;
}

UNexusCombinationRecipe* FNexusAssetCreation::CreateRecipe(
	const FString& PackagePath, const FString& DesiredName, UNexusItemDefinition* Output, FText& OutError)
{
	const FString Name = DesiredName.IsEmpty() ? TEXT("NewRecipe") : DesiredName;
	UNexusCombinationRecipe* Recipe = StampAsset<UNexusCombinationRecipe>(PackagePath, Name, OutError);
	if (!Recipe)
	{
		return nullptr;
	}
	if (Output)
	{
		Recipe->Output = Output;
	}
	return Recipe;
}

UNexusLevelManifest* FNexusAssetCreation::CreateManifest(
	const FString& PackagePath, const FString& DesiredName, FText& OutError)
{
	const FString Name = DesiredName.IsEmpty() ? TEXT("NewManifest") : DesiredName;
	return StampAsset<UNexusLevelManifest>(PackagePath, Name, OutError);
}

UNexusEquipmentLoadout* FNexusAssetCreation::CreateLoadout(
	const FString& PackagePath, const FString& DesiredName, FText& OutError)
{
	const FString Name = DesiredName.IsEmpty() ? TEXT("NewLoadout") : DesiredName;
	return StampAsset<UNexusEquipmentLoadout>(PackagePath, Name, OutError);
}

#undef LOCTEXT_NAMESPACE
