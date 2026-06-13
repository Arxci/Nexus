#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "NexusAssetFactories.generated.h"

/**
 * UFactory subclasses so the Nexus data-asset types appear under the content
 * browser's right-click **Create → Nexus** menu (the category comes from the
 * matching UAssetDefinition). Each just stamps a fresh instance; the user then
 * fills it in via the normal details panel — same end state as the Creator
 * window's "Create" buttons, but for designers who live in the content browser.
 */

UCLASS()
class UNexusItemDefinitionFactory : public UFactory
{
	GENERATED_BODY()
public:
	UNexusItemDefinitionFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

UCLASS()
class UNexusAttachmentDefinitionFactory : public UFactory
{
	GENERATED_BODY()
public:
	UNexusAttachmentDefinitionFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

UCLASS()
class UNexusCombinationRecipeFactory : public UFactory
{
	GENERATED_BODY()
public:
	UNexusCombinationRecipeFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

UCLASS()
class UNexusLevelManifestFactory : public UFactory
{
	GENERATED_BODY()
public:
	UNexusLevelManifestFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

UCLASS()
class UNexusEquipmentLoadoutFactory : public UFactory
{
	GENERATED_BODY()
public:
	UNexusEquipmentLoadoutFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

UCLASS()
class UNexusInputContextFactory : public UFactory
{
	GENERATED_BODY()
public:
	UNexusInputContextFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

UCLASS()
class UNexusInputConfigFactory : public UFactory
{
	GENERATED_BODY()
public:
	UNexusInputConfigFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
