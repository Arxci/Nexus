#pragma once

#include "CoreMinimal.h"
#include "UObject/WeakObjectPtr.h"

class FProperty;
class UClass;
class UFunction;
class UScriptStruct;
class UStruct;

/**
 * Pure data model behind the Nexus Docs browser. No Slate, no editor UI — just
 * reflection extraction so the walker can be exercised from tests and reused.
 *
 * The walker pulls everything UHT already records: ToolTip / ShortToolTip /
 * Category / Keywords / DisplayName metadata, function and property flags
 * (BlueprintCallable, BlueprintPure, BlueprintReadWrite, ...), parameter types
 * and names, and the source header path. UE only emits ToolTip metadata when
 * the C++ has a doxygen-style doc comment above the symbol, so descriptions
 * reflect how well the runtime code is documented.
 */

/** One input or return value on a function. */
struct FNexusDocParam
{
	/** Parameter name as declared in C++. */
	FString Name;
	/** Designer-friendly type ("Vector", "Integer", "Gameplay Tag", ...). */
	FString DisplayType;
	/** Exact C++ type for engineers ("FVector", "int32", "FGameplayTag"). */
	FString RawType;
	/** Per-parameter tooltip if UHT extracted one via @param. */
	FString Tooltip;

	bool bIsReturn = false;
	bool bIsOut = false;
	bool bIsReference = false;
	bool bIsConst = false;
	bool bHasDefault = false;
	FString DefaultValue;
};

/** One UFUNCTION declared on a class. */
struct FNexusDocFunction
{
	FString FunctionName;
	/** "DisplayName" metadata if present, otherwise the prettified function name. */
	FString DisplayName;
	FString Tooltip;
	FString ShortTooltip;
	/** UFUNCTION Category (the same string designers see in the Blueprint context menu). */
	FString Category;
	/** UFUNCTION Keywords metadata, for searching. */
	FString Keywords;

	bool bIsBlueprintCallable = false;
	bool bIsBlueprintPure = false;
	bool bIsBlueprintEvent = false; // BlueprintImplementableEvent / BlueprintNativeEvent
	bool bIsStatic = false;
	bool bIsConst = false;
	bool bIsServer = false;
	bool bIsClient = false;
	bool bIsNetMulticast = false;
	bool bIsLatent = false;
	bool bIsReliable = false;

	/** Parameters, NOT including the return value. */
	TArray<FNexusDocParam> Parameters;
	/** Return value if present (bIsReturn = true), otherwise empty Name. */
	FNexusDocParam ReturnValue;

	/** Pre-rendered "ReturnType FunctionName(Type Name, Type Name) const" for the header. */
	FString Signature;
};

/** One UPROPERTY declared on a class or struct. */
struct FNexusDocProperty
{
	FString PropertyName;
	FString DisplayName;
	FString DisplayType;
	FString RawType;
	FString Tooltip;
	FString Category;

	bool bBlueprintReadable = false;
	bool bBlueprintWritable = false;
	bool bEditAnywhere = false;
	bool bEditDefaultsOnly = false;
	bool bEditInstanceOnly = false;
	bool bSaveGame = false;
	bool bIsDelegate = false;     // BlueprintAssignable multicast — surfaced as an "Event"
	bool bIsReplicated = false;
};

/** One UCLASS / UScriptStruct entry. */
struct FNexusDocClass
{
	TWeakObjectPtr<UStruct> Struct;

	FString TypeName;       // "UNexusHealthComponent" / "FNexusDamageContext"
	FString DisplayName;    // "Nexus Health Component" (or DisplayName metadata)
	FString Category;       // top-level grouping derived from folder ("Combat", "Inventory", ...)
	FString Tooltip;
	FString ShortTooltip;
	FString ParentTypeName; // "UActorComponent" / empty for structs

	/** "Combat/NexusHealthComponent.h" — relative to the module's Source root. */
	FString HeaderPath;

	bool bIsStruct = false;
	bool bIsActor = false;
	bool bIsComponent = false;
	bool bIsSubsystem = false;
	bool bIsFunctionLibrary = false;
	bool bIsInterface = false;
	bool bIsAbstract = false;

	/** All UFUNCTIONs (BlueprintCallable / Pure / Event) declared on this type. */
	TArray<FNexusDocFunction> Functions;
	/** All UPROPERTYs that aren't BlueprintAssignable delegates. */
	TArray<FNexusDocProperty> Properties;
	/** BlueprintAssignable multicast delegates surfaced as a separate "Events" list. */
	TArray<FNexusDocProperty> Events;
};

/** A flat collection of every documented type, plus the categories used by the UI. */
struct FNexusDocCollection
{
	TArray<TSharedPtr<FNexusDocClass>> Classes;
	/** Distinct category names in display order. */
	TArray<FString> Categories;
};

namespace NexusDocs
{
	/**
	 * Walk the reflection database and return every UCLASS / UScriptStruct that
	 * lives in the runtime "Nexus" module. Classes with no Blueprint-exposed
	 * members are still emitted (so designers can see they exist) but will look
	 * empty in the detail panel.
	 */
	FNexusDocCollection BuildFromNexusModule();

	/** Designer-friendly rendering of an FProperty type. */
	FString FriendlyType(const FProperty* Property);
	/** Exact C++ rendering of an FProperty type. */
	FString RawType(const FProperty* Property);
}
