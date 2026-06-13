#include "AssetDefinitions/NexusAssetFactories.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"
#include "Nexus/Crafting/NexusCombinationRecipe.h"
#include "Nexus/Levels/NexusLevelManifest.h"
#include "Nexus/Equipment/NexusEquipmentLoadout.h"
#include "Nexus/Input/NexusInputContext.h"
#include "Nexus/Input/NexusInputConfig.h"

// --- Item --------------------------------------------------------------------
UNexusItemDefinitionFactory::UNexusItemDefinitionFactory()
{
	SupportedClass = UNexusItemDefinition::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UNexusItemDefinitionFactory::FactoryCreateNew(
	UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UNexusItemDefinition>(InParent, InClass, InName, Flags);
}

// --- Attachment --------------------------------------------------------------
UNexusAttachmentDefinitionFactory::UNexusAttachmentDefinitionFactory()
{
	SupportedClass = UNexusAttachmentDefinition::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UNexusAttachmentDefinitionFactory::FactoryCreateNew(
	UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UNexusAttachmentDefinition>(InParent, InClass, InName, Flags);
}

// --- Recipe ------------------------------------------------------------------
UNexusCombinationRecipeFactory::UNexusCombinationRecipeFactory()
{
	SupportedClass = UNexusCombinationRecipe::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UNexusCombinationRecipeFactory::FactoryCreateNew(
	UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UNexusCombinationRecipe>(InParent, InClass, InName, Flags);
}

// --- Level Manifest ----------------------------------------------------------
UNexusLevelManifestFactory::UNexusLevelManifestFactory()
{
	SupportedClass = UNexusLevelManifest::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UNexusLevelManifestFactory::FactoryCreateNew(
	UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UNexusLevelManifest>(InParent, InClass, InName, Flags);
}

// --- Equipment Loadout -------------------------------------------------------
UNexusEquipmentLoadoutFactory::UNexusEquipmentLoadoutFactory()
{
	SupportedClass = UNexusEquipmentLoadout::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UNexusEquipmentLoadoutFactory::FactoryCreateNew(
	UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UNexusEquipmentLoadout>(InParent, InClass, InName, Flags);
}

// --- Input Context -----------------------------------------------------------
UNexusInputContextFactory::UNexusInputContextFactory()
{
	SupportedClass = UNexusInputContext::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UNexusInputContextFactory::FactoryCreateNew(
	UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UNexusInputContext>(InParent, InClass, InName, Flags);
}

// --- Input Config ------------------------------------------------------------
UNexusInputConfigFactory::UNexusInputConfigFactory()
{
	SupportedClass = UNexusInputConfig::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UNexusInputConfigFactory::FactoryCreateNew(
	UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UNexusInputConfig>(InParent, InClass, InName, Flags);
}
