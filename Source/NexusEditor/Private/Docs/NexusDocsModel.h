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
 *
 * After the per-type walk a second pass derives cross-type information
 * designers care about — which subclasses inherit from a given class, which
 * classes hold a property of that type ("Used By"), and aggregate
 * documentation-coverage counters that drive the browser's header band.
 */

/** Coarse role used by the UI to colour-chip each entry and to drive type filters. */
enum class ENexusDocKind : uint8
{
	Class,
	Component,
	Subsystem,
	Library,        // UBlueprintFunctionLibrary
	Interface,
	Actor,
	Struct,
};

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

	/** True when UHT recorded a doxygen doc block on this function. */
	bool bHasDocs() const { return !Tooltip.IsEmpty(); }
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

	/**
	 * Resolved type-name of the underlying UStruct / UClass when the property
	 * references a Nexus reflected type. Empty for primitives or types from
	 * other modules. Used by the cross-reference pass to wire "Used By" links.
	 */
	FString ReferencedTypeName;

	bool bHasDocs() const { return !Tooltip.IsEmpty(); }
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

	/**
	 * Filled in a post-pass: every Nexus type whose parent type is this one
	 * (direct children only — the UI walks the chain transitively when it
	 * needs the full subtree).
	 */
	TArray<FString> DerivedTypeNames;

	/**
	 * Filled in a post-pass: every Nexus type that has a UPROPERTY whose
	 * resolved class / struct type is this one. Designers use this to find
	 * "where does Nexus actually consume this thing?"
	 */
	TArray<FString> ReferencedByTypeNames;

	bool bHasDocs() const { return !Tooltip.IsEmpty(); }

	/** Distilled type kind for chips and filters. Mirrors the bool flags. */
	ENexusDocKind Kind() const
	{
		if (bIsStruct)           { return ENexusDocKind::Struct; }
		if (bIsInterface)        { return ENexusDocKind::Interface; }
		if (bIsSubsystem)        { return ENexusDocKind::Subsystem; }
		if (bIsFunctionLibrary)  { return ENexusDocKind::Library; }
		if (bIsComponent)        { return ENexusDocKind::Component; }
		if (bIsActor)            { return ENexusDocKind::Actor; }
		return ENexusDocKind::Class;
	}
};

/** A flat collection of every documented type, plus aggregate stats used by the UI. */
struct FNexusDocCollection
{
	TArray<TSharedPtr<FNexusDocClass>> Classes;
	/** Distinct category names in display order. */
	TArray<FString> Categories;
	/** TypeName -> entry, for O(1) lookup (Used-By / parent links) instead of scanning Classes. */
	TMap<FString, TSharedPtr<FNexusDocClass>> ByName;

	// === Aggregate counters (computed during BuildFromNexusModule) ===========
	int32 TotalClasses = 0;          // UCLASS count
	int32 TotalStructs = 0;          // UScriptStruct count
	int32 TotalFunctions = 0;        // UFUNCTIONs across all classes
	int32 TotalProperties = 0;       // UPROPERTYs (non-delegate)
	int32 TotalEvents = 0;           // BlueprintAssignable delegate UPROPERTYs

	int32 DocumentedClasses = 0;     // classes/structs with a /** doc comment */
	int32 DocumentedMembers = 0;     // functions + properties + events with doc comments
	int32 TotalMembers = 0;          // Functions + Properties + Events
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

	/** Quick lookup by raw C++ type name. Returns null when the name isn't a Nexus type. */
	TSharedPtr<FNexusDocClass> FindByTypeName(const FNexusDocCollection& Collection, const FString& TypeName);

	/** Designer-friendly rendering of an FProperty type. */
	FString FriendlyType(const FProperty* Property);
	/** Exact C++ rendering of an FProperty type. */
	FString RawType(const FProperty* Property);

	/** Short label for the type-kind chip ("CLASS", "STRUCT", "SUB", "LIB", ...). */
	FString KindShortLabel(ENexusDocKind Kind);
	/** Verbose label used in tooltips and the legend ("Function Library", "Subsystem", ...). */
	FString KindLongLabel(ENexusDocKind Kind);

	/**
	 * Render the whole collection as one self-contained Markdown document:
	 * a coverage summary, then a section per category, then a sub-section per
	 * type listing its description, inheritance, functions (with signatures,
	 * parameters, and returns), properties, and events. Pure and deterministic
	 * so it can be diffed, committed, or published as a static reference, and
	 * so it can be exercised from tests without any Slate / editor UI.
	 */
	FString ExportMarkdown(const FNexusDocCollection& Collection);
}
