#include "Docs/NexusDocsModel.h"

#include "UObject/Class.h"
#include "UObject/Package.h"
#include "UObject/UnrealType.h"
#include "UObject/UObjectIterator.h"

#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Subsystems/Subsystem.h"

namespace
{
	/** Package name for the Nexus runtime module. Used to filter the reflection iterator. */
	const TCHAR* NexusModulePackage = TEXT("/Script/Nexus");

	/**
	 * Insert spaces in a CamelCase / PascalCase identifier so it reads like a
	 * label: "ApplyDamageToActor" -> "Apply Damage To Actor". We also strip the
	 * conventional U/A/F/E/I single-letter prefixes from type names so designers
	 * see "Nexus Health Component" rather than "U Nexus Health Component".
	 */
	FString PrettifyIdentifier(const FString& Identifier, bool bStripTypePrefix)
	{
		if (Identifier.IsEmpty())
		{
			return Identifier;
		}

		FString Working = Identifier;
		if (bStripTypePrefix && Working.Len() >= 2 && FChar::IsUpper(Working[0]) && FChar::IsUpper(Working[1]))
		{
			const TCHAR First = Working[0];
			if (First == TEXT('U') || First == TEXT('A') || First == TEXT('F') || First == TEXT('E') || First == TEXT('I'))
			{
				Working.RemoveAt(0, 1);
			}
		}

		FString Out;
		Out.Reserve(Working.Len() + 8);
		for (int32 Index = 0; Index < Working.Len(); ++Index)
		{
			const TCHAR Ch = Working[Index];
			if (Index > 0 && FChar::IsUpper(Ch))
			{
				const TCHAR Prev = Working[Index - 1];
				const bool bPrevLower = FChar::IsLower(Prev);
				const bool bPrevDigit = FChar::IsDigit(Prev);
				const bool bNextLower = (Index + 1 < Working.Len()) && FChar::IsLower(Working[Index + 1]);
				if (bPrevLower || bPrevDigit || (FChar::IsUpper(Prev) && bNextLower))
				{
					Out.AppendChar(TEXT(' '));
				}
			}
			Out.AppendChar(Ch);
		}
		return Out;
	}

	/**
	 * Designer-facing struct name. "FNexusDamageContext" -> "Nexus Damage Context",
	 * "FVector" -> "Vector", "FGameplayTag" -> "Gameplay Tag". A short alias table
	 * handles the engine primitives every designer recognises.
	 */
	FString FriendlyStructName(const UScriptStruct* Struct)
	{
		if (!Struct)
		{
			return TEXT("Struct");
		}
		const FString Name = Struct->GetName();
		static const TMap<FString, FString> Aliases = {
			{ TEXT("Vector"),               TEXT("Vector") },
			{ TEXT("Vector2D"),             TEXT("Vector 2D") },
			{ TEXT("Vector4"),              TEXT("Vector 4") },
			{ TEXT("IntVector"),            TEXT("Integer Vector") },
			{ TEXT("IntPoint"),             TEXT("Integer Point") },
			{ TEXT("Rotator"),              TEXT("Rotator") },
			{ TEXT("Quat"),                 TEXT("Quaternion") },
			{ TEXT("Transform"),            TEXT("Transform") },
			{ TEXT("LinearColor"),          TEXT("Linear Color") },
			{ TEXT("Color"),                TEXT("Color") },
			{ TEXT("Box"),                  TEXT("Box") },
			{ TEXT("Plane"),                TEXT("Plane") },
			{ TEXT("HitResult"),            TEXT("Hit Result") },
			{ TEXT("DateTime"),             TEXT("Date Time") },
			{ TEXT("Timespan"),             TEXT("Timespan") },
			{ TEXT("GameplayTag"),          TEXT("Gameplay Tag") },
			{ TEXT("GameplayTagContainer"), TEXT("Gameplay Tag Container") },
			{ TEXT("Guid"),                 TEXT("GUID") },
		};
		if (const FString* Mapped = Aliases.Find(Name))
		{
			return *Mapped;
		}
		return PrettifyIdentifier(Name, /*bStripTypePrefix=*/false);
	}

	FString FriendlyClassName(const UClass* Class)
	{
		if (!Class)
		{
			return TEXT("Object");
		}
		return PrettifyIdentifier(Class->GetName(), /*bStripTypePrefix=*/true);
	}

	/**
	 * Translate an FProperty into a one-line type label. Container properties
	 * recurse into their inner type so designers see "Array of Gameplay Tag"
	 * rather than "TArray". Object/class properties name the pointee class.
	 */
	FString FriendlyTypeInternal(const FProperty* Property)
	{
		if (!Property)
		{
			return FString();
		}

		if (CastField<FBoolProperty>(Property))   { return TEXT("Boolean"); }
		if (CastField<FInt8Property>(Property))   { return TEXT("Integer (8-bit)"); }
		if (CastField<FInt16Property>(Property))  { return TEXT("Integer (16-bit)"); }
		if (CastField<FIntProperty>(Property))    { return TEXT("Integer"); }
		if (CastField<FInt64Property>(Property))  { return TEXT("Integer (64-bit)"); }
		if (CastField<FUInt16Property>(Property)) { return TEXT("Integer (16-bit, unsigned)"); }
		if (CastField<FUInt32Property>(Property)) { return TEXT("Integer (unsigned)"); }
		if (CastField<FUInt64Property>(Property)) { return TEXT("Integer (64-bit, unsigned)"); }
		if (CastField<FFloatProperty>(Property))  { return TEXT("Float"); }
		if (CastField<FDoubleProperty>(Property)) { return TEXT("Float (Double)"); }
		if (CastField<FStrProperty>(Property))    { return TEXT("String"); }
		if (CastField<FNameProperty>(Property))   { return TEXT("Name"); }
		if (CastField<FTextProperty>(Property))   { return TEXT("Text"); }

		if (const FByteProperty* ByteProp = CastField<FByteProperty>(Property))
		{
			if (ByteProp->Enum)
			{
				return PrettifyIdentifier(ByteProp->Enum->GetName(), /*bStripTypePrefix=*/true);
			}
			return TEXT("Byte");
		}
		if (const FEnumProperty* EnumProp = CastField<FEnumProperty>(Property))
		{
			if (EnumProp->GetEnum())
			{
				return PrettifyIdentifier(EnumProp->GetEnum()->GetName(), /*bStripTypePrefix=*/true);
			}
			return TEXT("Enum");
		}

		if (const FStructProperty* StructProp = CastField<FStructProperty>(Property))
		{
			return FriendlyStructName(StructProp->Struct);
		}

		if (const FClassProperty* ClassProp = CastField<FClassProperty>(Property))
		{
			return FString::Printf(TEXT("%s Class"), *FriendlyClassName(ClassProp->MetaClass));
		}
		if (const FSoftClassProperty* SoftClassProp = CastField<FSoftClassProperty>(Property))
		{
			return FString::Printf(TEXT("%s Class (Soft)"), *FriendlyClassName(SoftClassProp->MetaClass));
		}
		if (const FSoftObjectProperty* SoftObjProp = CastField<FSoftObjectProperty>(Property))
		{
			return FString::Printf(TEXT("%s Reference (Soft)"), *FriendlyClassName(SoftObjProp->PropertyClass));
		}
		if (const FWeakObjectProperty* WeakObjProp = CastField<FWeakObjectProperty>(Property))
		{
			return FString::Printf(TEXT("%s Reference (Weak)"), *FriendlyClassName(WeakObjProp->PropertyClass));
		}
		if (const FObjectProperty* ObjProp = CastField<FObjectProperty>(Property))
		{
			return FString::Printf(TEXT("%s Reference"), *FriendlyClassName(ObjProp->PropertyClass));
		}
		if (const FInterfaceProperty* InterfaceProp = CastField<FInterfaceProperty>(Property))
		{
			return FString::Printf(TEXT("%s Interface"), *FriendlyClassName(InterfaceProp->InterfaceClass));
		}

		if (const FArrayProperty* ArrayProp = CastField<FArrayProperty>(Property))
		{
			return FString::Printf(TEXT("Array of %s"), *FriendlyTypeInternal(ArrayProp->Inner));
		}
		if (const FSetProperty* SetProp = CastField<FSetProperty>(Property))
		{
			return FString::Printf(TEXT("Set of %s"), *FriendlyTypeInternal(SetProp->ElementProp));
		}
		if (const FMapProperty* MapProp = CastField<FMapProperty>(Property))
		{
			return FString::Printf(TEXT("Map of %s → %s"),
				*FriendlyTypeInternal(MapProp->KeyProp),
				*FriendlyTypeInternal(MapProp->ValueProp));
		}

		if (CastField<FDelegateProperty>(Property) || CastField<FMulticastDelegateProperty>(Property))
		{
			return TEXT("Event");
		}

		// Fallback to the engine's CPP type string.
		return Property->GetCPPType();
	}

	FString RawTypeInternal(const FProperty* Property)
	{
		if (!Property)
		{
			return FString();
		}
		FString ExtendedType;
		FString Base = Property->GetCPPType(&ExtendedType, CPPF_None);
		return Base + ExtendedType;
	}

	/**
	 * If a property references a UClass / UScriptStruct, return the raw type
	 * name ("UNexusItemDefinition" / "FNexusFragment_Weapon"). The cross-
	 * reference pass uses this to wire "Used By" links. Returns empty when the
	 * property is a primitive, an external-module type we don't track, or a
	 * container — containers are handled by recursing into their inner property.
	 */
	FString ResolveReferencedType(const FProperty* Property)
	{
		if (!Property)
		{
			return FString();
		}
		if (const FStructProperty* StructProp = CastField<FStructProperty>(Property))
		{
			return StructProp->Struct ? StructProp->Struct->GetName() : FString();
		}
		if (const FClassProperty* ClassProp = CastField<FClassProperty>(Property))
		{
			return ClassProp->MetaClass ? ClassProp->MetaClass->GetName() : FString();
		}
		if (const FSoftClassProperty* SoftClassProp = CastField<FSoftClassProperty>(Property))
		{
			return SoftClassProp->MetaClass ? SoftClassProp->MetaClass->GetName() : FString();
		}
		if (const FSoftObjectProperty* SoftObjProp = CastField<FSoftObjectProperty>(Property))
		{
			return SoftObjProp->PropertyClass ? SoftObjProp->PropertyClass->GetName() : FString();
		}
		if (const FWeakObjectProperty* WeakObjProp = CastField<FWeakObjectProperty>(Property))
		{
			return WeakObjProp->PropertyClass ? WeakObjProp->PropertyClass->GetName() : FString();
		}
		if (const FObjectProperty* ObjProp = CastField<FObjectProperty>(Property))
		{
			return ObjProp->PropertyClass ? ObjProp->PropertyClass->GetName() : FString();
		}
		if (const FInterfaceProperty* InterfaceProp = CastField<FInterfaceProperty>(Property))
		{
			return InterfaceProp->InterfaceClass ? InterfaceProp->InterfaceClass->GetName() : FString();
		}
		if (const FArrayProperty* ArrayProp = CastField<FArrayProperty>(Property))
		{
			return ResolveReferencedType(ArrayProp->Inner);
		}
		if (const FSetProperty* SetProp = CastField<FSetProperty>(Property))
		{
			return ResolveReferencedType(SetProp->ElementProp);
		}
		if (const FMapProperty* MapProp = CastField<FMapProperty>(Property))
		{
			// Both halves of a map can reference other Nexus types; prefer the
			// value side (it's what designers usually want to follow).
			FString FromValue = ResolveReferencedType(MapProp->ValueProp);
			return FromValue.IsEmpty() ? ResolveReferencedType(MapProp->KeyProp) : FromValue;
		}
		return FString();
	}

	/**
	 * UHT stores per-parameter tooltips in the function's "ToolTip" metadata as a
	 * blob with "@param Name description" lines. Pull the line that matches.
	 */
	FString ExtractParamTooltip(const FString& FunctionTooltip, const FString& ParamName)
	{
		if (FunctionTooltip.IsEmpty() || ParamName.IsEmpty())
		{
			return FString();
		}
		// Match "@param ParamName ..." (case-insensitive on the tag, exact on the name).
		const FString Marker = FString::Printf(TEXT("@param %s"), *ParamName);
		const int32 Start = FunctionTooltip.Find(Marker, ESearchCase::IgnoreCase);
		if (Start == INDEX_NONE)
		{
			return FString();
		}
		int32 LineEnd = FunctionTooltip.Find(TEXT("\n"), ESearchCase::IgnoreCase, ESearchDir::FromStart, Start);
		if (LineEnd == INDEX_NONE)
		{
			LineEnd = FunctionTooltip.Len();
		}
		FString Line = FunctionTooltip.Mid(Start + Marker.Len(), LineEnd - Start - Marker.Len());
		Line.TrimStartAndEndInline();
		return Line;
	}

	/** UHT stores the @return / @returns description the same way. */
	FString ExtractReturnTooltip(const FString& FunctionTooltip)
	{
		if (FunctionTooltip.IsEmpty())
		{
			return FString();
		}
		for (const TCHAR* Tag : { TEXT("@return"), TEXT("@returns") })
		{
			const int32 Start = FunctionTooltip.Find(Tag, ESearchCase::IgnoreCase);
			if (Start == INDEX_NONE)
			{
				continue;
			}
			const int32 TagLen = FCString::Strlen(Tag);
			int32 LineEnd = FunctionTooltip.Find(TEXT("\n"), ESearchCase::IgnoreCase, ESearchDir::FromStart, Start);
			if (LineEnd == INDEX_NONE)
			{
				LineEnd = FunctionTooltip.Len();
			}
			FString Line = FunctionTooltip.Mid(Start + TagLen, LineEnd - Start - TagLen);
			Line.TrimStartAndEndInline();
			return Line;
		}
		return FString();
	}

	/**
	 * UHT prepends every doc-comment paragraph with "@param ...", "@return ...".
	 * For the summary tooltip we strip those lines so designers see prose only.
	 */
	FString StripTags(const FString& Tooltip)
	{
		if (Tooltip.IsEmpty())
		{
			return Tooltip;
		}
		FString Out;
		Out.Reserve(Tooltip.Len());
		TArray<FString> Lines;
		Tooltip.ParseIntoArrayLines(Lines, /*bCullEmpty=*/false);
		for (const FString& Line : Lines)
		{
			FString Trimmed = Line;
			Trimmed.TrimStartInline();
			if (Trimmed.StartsWith(TEXT("@")))
			{
				continue;
			}
			if (!Out.IsEmpty())
			{
				Out.AppendChar(TEXT('\n'));
			}
			Out.Append(Line);
		}
		Out.TrimStartAndEndInline();
		return Out;
	}

	/**
	 * Derive a top-level category from the source folder. ModuleRelativePath is
	 * "Combat/NexusHealthComponent.h" -> "Combat". Files at the module root
	 * (no folder) fall under "Core".
	 */
	FString CategoryFromHeaderPath(const FString& HeaderPath)
	{
		if (HeaderPath.IsEmpty())
		{
			return TEXT("Core");
		}
		int32 Slash = INDEX_NONE;
		if (HeaderPath.FindChar(TEXT('/'), Slash) && Slash > 0)
		{
			return HeaderPath.Left(Slash);
		}
		return TEXT("Core");
	}

	void PopulateParam(FProperty* Prop, const FString& FunctionTooltip, FNexusDocParam& OutParam)
	{
		OutParam.Name = Prop->GetName();
		OutParam.DisplayType = FriendlyTypeInternal(Prop);
		OutParam.RawType = RawTypeInternal(Prop);
		OutParam.Tooltip = ExtractParamTooltip(FunctionTooltip, OutParam.Name);
		OutParam.bIsReturn = Prop->HasAnyPropertyFlags(CPF_ReturnParm);
		OutParam.bIsOut = Prop->HasAnyPropertyFlags(CPF_OutParm) && !Prop->HasAnyPropertyFlags(CPF_ConstParm);
		OutParam.bIsReference = Prop->HasAnyPropertyFlags(CPF_ReferenceParm);
		OutParam.bIsConst = Prop->HasAnyPropertyFlags(CPF_ConstParm);
		// UFUNCTION default values live in metadata as "CPP_Default_<ParamName>".
		const FString DefaultKey = FString::Printf(TEXT("CPP_Default_%s"), *OutParam.Name);
		if (UFunction* OwningFunc = Prop->GetOwner<UFunction>())
		{
			if (OwningFunc->HasMetaData(*DefaultKey))
			{
				OutParam.bHasDefault = true;
				OutParam.DefaultValue = OwningFunc->GetMetaData(*DefaultKey);
			}
		}
	}

	FString BuildSignature(const FNexusDocFunction& Func)
	{
		FString Args;
		for (int32 Index = 0; Index < Func.Parameters.Num(); ++Index)
		{
			if (Index > 0)
			{
				Args.Append(TEXT(", "));
			}
			const FNexusDocParam& Param = Func.Parameters[Index];
			FString Qualifier;
			if (Param.bIsOut)
			{
				Qualifier = TEXT("out ");
			}
			Args.Append(FString::Printf(TEXT("%s%s: %s"), *Qualifier, *Param.Name, *Param.DisplayType));
			if (Param.bHasDefault)
			{
				Args.Append(FString::Printf(TEXT(" = %s"), *Param.DefaultValue));
			}
		}

		const FString ReturnType = Func.ReturnValue.Name.IsEmpty() ? TEXT("void") : Func.ReturnValue.DisplayType;
		FString Result = FString::Printf(TEXT("%s %s(%s)"), *ReturnType, *Func.FunctionName, *Args);
		if (Func.bIsConst)
		{
			Result.Append(TEXT(" const"));
		}
		return Result;
	}

	void PopulateFunction(UFunction* Func, FNexusDocFunction& OutFunc)
	{
		OutFunc.FunctionName = Func->GetName();
		OutFunc.DisplayName = Func->HasMetaData(TEXT("DisplayName"))
			? Func->GetMetaData(TEXT("DisplayName"))
			: PrettifyIdentifier(OutFunc.FunctionName, /*bStripTypePrefix=*/false);

		const FString RawTooltip = Func->GetMetaData(TEXT("ToolTip"));
		OutFunc.Tooltip = StripTags(RawTooltip);
		OutFunc.ShortTooltip = Func->GetMetaData(TEXT("ShortToolTip"));
		OutFunc.Category = Func->GetMetaData(TEXT("Category"));
		OutFunc.Keywords = Func->GetMetaData(TEXT("Keywords"));

		const EFunctionFlags Flags = Func->FunctionFlags;
		OutFunc.bIsBlueprintCallable = (Flags & FUNC_BlueprintCallable) != 0;
		OutFunc.bIsBlueprintPure     = (Flags & FUNC_BlueprintPure) != 0;
		OutFunc.bIsBlueprintEvent    = (Flags & FUNC_BlueprintEvent) != 0;
		OutFunc.bIsStatic            = (Flags & FUNC_Static) != 0;
		OutFunc.bIsConst             = (Flags & FUNC_Const) != 0;
		OutFunc.bIsServer            = (Flags & FUNC_NetServer) != 0;
		OutFunc.bIsClient            = (Flags & FUNC_NetClient) != 0;
		OutFunc.bIsNetMulticast      = (Flags & FUNC_NetMulticast) != 0;
		OutFunc.bIsReliable          = (Flags & FUNC_NetReliable) != 0;
		OutFunc.bIsLatent            = Func->HasMetaData(TEXT("Latent"));

		for (TFieldIterator<FProperty> It(Func); It; ++It)
		{
			FProperty* Prop = *It;
			if (!Prop->HasAnyPropertyFlags(CPF_Parm))
			{
				continue;
			}
			FNexusDocParam Param;
			PopulateParam(Prop, RawTooltip, Param);
			if (Param.bIsReturn)
			{
				OutFunc.ReturnValue = MoveTemp(Param);
				OutFunc.ReturnValue.Tooltip = ExtractReturnTooltip(RawTooltip);
			}
			else
			{
				OutFunc.Parameters.Add(MoveTemp(Param));
			}
		}

		OutFunc.Signature = BuildSignature(OutFunc);
	}

	void PopulateProperty(FProperty* Prop, FNexusDocProperty& OutProp)
	{
		OutProp.PropertyName = Prop->GetName();
		OutProp.DisplayName = Prop->HasMetaData(TEXT("DisplayName"))
			? Prop->GetMetaData(TEXT("DisplayName"))
			: PrettifyIdentifier(OutProp.PropertyName, /*bStripTypePrefix=*/false);
		OutProp.DisplayType = FriendlyTypeInternal(Prop);
		OutProp.RawType = RawTypeInternal(Prop);
		OutProp.Tooltip = StripTags(Prop->GetMetaData(TEXT("ToolTip")));
		OutProp.Category = Prop->GetMetaData(TEXT("Category"));
		OutProp.ReferencedTypeName = ResolveReferencedType(Prop);

		const EPropertyFlags Flags = Prop->GetPropertyFlags();
		OutProp.bBlueprintReadable = (Flags & CPF_BlueprintVisible) != 0;
		OutProp.bBlueprintWritable = OutProp.bBlueprintReadable && (Flags & CPF_BlueprintReadOnly) == 0;
		OutProp.bEditAnywhere      = (Flags & CPF_Edit) != 0 && (Flags & CPF_DisableEditOnTemplate) == 0 && (Flags & CPF_DisableEditOnInstance) == 0;
		OutProp.bEditDefaultsOnly  = (Flags & CPF_Edit) != 0 && (Flags & CPF_DisableEditOnInstance) != 0;
		OutProp.bEditInstanceOnly  = (Flags & CPF_Edit) != 0 && (Flags & CPF_DisableEditOnTemplate) != 0;
		OutProp.bSaveGame          = (Flags & CPF_SaveGame) != 0;
		OutProp.bIsReplicated      = (Flags & CPF_Net) != 0;
		OutProp.bIsDelegate        = CastField<FMulticastDelegateProperty>(Prop) != nullptr
			|| CastField<FDelegateProperty>(Prop) != nullptr;
	}

	/**
	 * UCLASS-only flags: actor, component, subsystem, function library. Lets the
	 * UI badge classes ("Component", "Subsystem") so designers can scan the tree.
	 */
	void TagClassRole(UClass* Class, FNexusDocClass& OutEntry)
	{
		OutEntry.bIsAbstract = Class->HasAnyClassFlags(CLASS_Abstract);
		OutEntry.bIsInterface = Class->HasAnyClassFlags(CLASS_Interface);
		if (Class->IsChildOf(AActor::StaticClass()))
		{
			OutEntry.bIsActor = true;
		}
		if (Class->IsChildOf(UActorComponent::StaticClass()))
		{
			OutEntry.bIsComponent = true;
		}
		if (Class->IsChildOf(USubsystem::StaticClass()))
		{
			OutEntry.bIsSubsystem = true;
		}
		if (Class->IsChildOf(UBlueprintFunctionLibrary::StaticClass()))
		{
			OutEntry.bIsFunctionLibrary = true;
		}
	}

	/**
	 * Decide whether a class is interesting enough to list in the docs. Skip the
	 * generated SKEL_ / REINST_ / HOTRELOADED_ ghosts the editor creates while
	 * iterating Blueprints, plus anything explicitly marked Hidden/Deprecated.
	 */
	bool ShouldIncludeClass(UClass* Class)
	{
		if (!Class)
		{
			return false;
		}
		if (Class->HasAnyClassFlags(CLASS_NewerVersionExists | CLASS_Deprecated | CLASS_Hidden))
		{
			return false;
		}
		const FString Name = Class->GetName();
		if (Name.StartsWith(TEXT("SKEL_")) || Name.StartsWith(TEXT("REINST_"))
			|| Name.StartsWith(TEXT("HOTRELOADED_")) || Name.StartsWith(TEXT("TRASHCLASS_"))
			|| Name.StartsWith(TEXT("PLACEHOLDER-")))
		{
			return false;
		}
		// CLASS_CompiledFromBlueprint guards against Blueprint-generated classes
		// the asset registry surfaces if a Blueprint inherits from a Nexus C++ class.
		if (Class->HasAnyClassFlags(CLASS_CompiledFromBlueprint))
		{
			return false;
		}
		return true;
	}

	bool IsInNexusModule(UStruct* Type)
	{
		if (!Type)
		{
			return false;
		}
		UPackage* Package = Type->GetPackage();
		return Package && Package->GetName() == NexusModulePackage;
	}

	void PopulateClass(UClass* Class, FNexusDocClass& OutEntry)
	{
		OutEntry.Struct = Class;
		OutEntry.TypeName = Class->GetName();
		OutEntry.DisplayName = Class->HasMetaData(TEXT("DisplayName"))
			? Class->GetMetaData(TEXT("DisplayName"))
			: PrettifyIdentifier(OutEntry.TypeName, /*bStripTypePrefix=*/true);
		OutEntry.Tooltip = StripTags(Class->GetMetaData(TEXT("ToolTip")));
		OutEntry.ShortTooltip = Class->GetMetaData(TEXT("ShortToolTip"));
		OutEntry.ParentTypeName = Class->GetSuperClass() ? Class->GetSuperClass()->GetName() : FString();
		OutEntry.HeaderPath = Class->GetMetaData(TEXT("ModuleRelativePath"));
		OutEntry.Category = CategoryFromHeaderPath(OutEntry.HeaderPath);
		OutEntry.bIsStruct = false;
		TagClassRole(Class, OutEntry);

		// Walk only the functions declared on this class (ExcludeSuper). The
		// GetOwnerClass() guard below is belt-and-braces against engine versions
		// that still walk through generated container helpers.
		for (TFieldIterator<UFunction> It(Class, EFieldIteratorFlags::ExcludeSuper); It; ++It)
		{
			UFunction* Func = *It;
			if (Func->GetOwnerClass() != Class)
			{
				continue;
			}
			const EFunctionFlags Flags = Func->FunctionFlags;
			const bool bExposed = (Flags & (FUNC_BlueprintCallable | FUNC_BlueprintPure | FUNC_BlueprintEvent)) != 0;
			if (!bExposed)
			{
				continue;
			}
			FNexusDocFunction Entry;
			PopulateFunction(Func, Entry);
			OutEntry.Functions.Add(MoveTemp(Entry));
		}
		OutEntry.Functions.Sort([](const FNexusDocFunction& A, const FNexusDocFunction& B)
		{
			if (A.Category != B.Category)
			{
				return A.Category < B.Category;
			}
			return A.DisplayName < B.DisplayName;
		});

		for (TFieldIterator<FProperty> It(Class, EFieldIteratorFlags::ExcludeSuper); It; ++It)
		{
			FProperty* Prop = *It;
			if (Prop->GetOwnerClass() != Class)
			{
				continue;
			}
			if (!Prop->HasAnyPropertyFlags(CPF_BlueprintVisible | CPF_Edit | CPF_BlueprintAssignable))
			{
				continue;
			}
			FNexusDocProperty Entry;
			PopulateProperty(Prop, Entry);
			const bool bIsAssignable = Prop->HasAnyPropertyFlags(CPF_BlueprintAssignable);
			if (bIsAssignable)
			{
				Entry.bIsDelegate = true;
				OutEntry.Events.Add(MoveTemp(Entry));
			}
			else
			{
				OutEntry.Properties.Add(MoveTemp(Entry));
			}
		}
		auto ByName = [](const FNexusDocProperty& A, const FNexusDocProperty& B)
		{
			if (A.Category != B.Category)
			{
				return A.Category < B.Category;
			}
			return A.DisplayName < B.DisplayName;
		};
		OutEntry.Properties.Sort(ByName);
		OutEntry.Events.Sort(ByName);
	}

	void PopulateStruct(UScriptStruct* Struct, FNexusDocClass& OutEntry)
	{
		OutEntry.Struct = Struct;
		OutEntry.TypeName = Struct->GetName();
		OutEntry.DisplayName = Struct->HasMetaData(TEXT("DisplayName"))
			? Struct->GetMetaData(TEXT("DisplayName"))
			: FriendlyStructName(Struct);
		OutEntry.Tooltip = StripTags(Struct->GetMetaData(TEXT("ToolTip")));
		OutEntry.ShortTooltip = Struct->GetMetaData(TEXT("ShortToolTip"));
		OutEntry.ParentTypeName = Struct->GetSuperStruct() ? Struct->GetSuperStruct()->GetName() : FString();
		OutEntry.HeaderPath = Struct->GetMetaData(TEXT("ModuleRelativePath"));
		OutEntry.Category = CategoryFromHeaderPath(OutEntry.HeaderPath);
		OutEntry.bIsStruct = true;

		for (TFieldIterator<FProperty> It(Struct, EFieldIteratorFlags::ExcludeSuper); It; ++It)
		{
			FProperty* Prop = *It;
			if (Prop->GetOwnerStruct() != Struct)
			{
				continue;
			}
			if (!Prop->HasAnyPropertyFlags(CPF_BlueprintVisible | CPF_Edit))
			{
				continue;
			}
			FNexusDocProperty Entry;
			PopulateProperty(Prop, Entry);
			OutEntry.Properties.Add(MoveTemp(Entry));
		}
		OutEntry.Properties.Sort([](const FNexusDocProperty& A, const FNexusDocProperty& B)
		{
			return A.DisplayName < B.DisplayName;
		});
	}

	/**
	 * Cross-reference pass: every Nexus type knows about its parent already
	 * (ParentTypeName); flip that into "children" lists, and accumulate
	 * "Used By" sets from each property's resolved type. Runs once after the
	 * per-type walks so a single O(N + M) pass produces every back-link the
	 * detail panel needs.
	 */
	void BuildCrossReferences(FNexusDocCollection& Collection)
	{
		TMap<FString, FNexusDocClass*> Lookup;
		Lookup.Reserve(Collection.Classes.Num());
		for (const TSharedPtr<FNexusDocClass>& Entry : Collection.Classes)
		{
			if (Entry.IsValid())
			{
				Lookup.Add(Entry->TypeName, Entry.Get());
			}
		}

		// Parent → derived (only when the parent is a Nexus type itself).
		for (const TSharedPtr<FNexusDocClass>& Entry : Collection.Classes)
		{
			if (!Entry.IsValid() || Entry->ParentTypeName.IsEmpty())
			{
				continue;
			}
			if (FNexusDocClass** Parent = Lookup.Find(Entry->ParentTypeName))
			{
				(*Parent)->DerivedTypeNames.Add(Entry->TypeName);
			}
		}

		// Property type → referencing class. A class is added at most once per
		// referenced type even if it has multiple properties of that type.
		for (const TSharedPtr<FNexusDocClass>& Entry : Collection.Classes)
		{
			if (!Entry.IsValid())
			{
				continue;
			}
			TSet<FString> SeenRefs;
			auto ConsumeProperty = [&Lookup, &SeenRefs, &Entry](const FNexusDocProperty& Prop)
			{
				if (Prop.ReferencedTypeName.IsEmpty() || Prop.ReferencedTypeName == Entry->TypeName)
				{
					return;
				}
				if (SeenRefs.Contains(Prop.ReferencedTypeName))
				{
					return;
				}
				if (FNexusDocClass** Target = Lookup.Find(Prop.ReferencedTypeName))
				{
					(*Target)->ReferencedByTypeNames.Add(Entry->TypeName);
					SeenRefs.Add(Prop.ReferencedTypeName);
				}
			};
			for (const FNexusDocProperty& Prop : Entry->Properties) { ConsumeProperty(Prop); }
			for (const FNexusDocProperty& Prop : Entry->Events)     { ConsumeProperty(Prop); }
		}

		// Both link lists read better alphabetically.
		for (const TSharedPtr<FNexusDocClass>& Entry : Collection.Classes)
		{
			if (Entry.IsValid())
			{
				Entry->DerivedTypeNames.Sort();
				Entry->ReferencedByTypeNames.Sort();
			}
		}
	}

	/**
	 * Sum the per-class counts into the collection-level summary. The browser
	 * header band shows "X classes, Y% documented" off these.
	 */
	void ComputeAggregateStats(FNexusDocCollection& Collection)
	{
		Collection.TotalClasses = 0;
		Collection.TotalStructs = 0;
		Collection.TotalFunctions = 0;
		Collection.TotalProperties = 0;
		Collection.TotalEvents = 0;
		Collection.DocumentedClasses = 0;
		Collection.DocumentedMembers = 0;
		Collection.TotalMembers = 0;

		for (const TSharedPtr<FNexusDocClass>& Entry : Collection.Classes)
		{
			if (!Entry.IsValid())
			{
				continue;
			}
			if (Entry->bIsStruct) { ++Collection.TotalStructs; }
			else                  { ++Collection.TotalClasses; }
			if (Entry->bHasDocs()) { ++Collection.DocumentedClasses; }

			Collection.TotalFunctions  += Entry->Functions.Num();
			Collection.TotalProperties += Entry->Properties.Num();
			Collection.TotalEvents     += Entry->Events.Num();

			for (const FNexusDocFunction& Func : Entry->Functions)
			{
				++Collection.TotalMembers;
				if (Func.bHasDocs()) { ++Collection.DocumentedMembers; }
			}
			for (const FNexusDocProperty& Prop : Entry->Properties)
			{
				++Collection.TotalMembers;
				if (Prop.bHasDocs()) { ++Collection.DocumentedMembers; }
			}
			for (const FNexusDocProperty& Event : Entry->Events)
			{
				++Collection.TotalMembers;
				if (Event.bHasDocs()) { ++Collection.DocumentedMembers; }
			}
		}
	}
}

namespace NexusDocs
{
	FString FriendlyType(const FProperty* Property)
	{
		return FriendlyTypeInternal(Property);
	}

	FString RawType(const FProperty* Property)
	{
		return RawTypeInternal(Property);
	}

	FString KindShortLabel(ENexusDocKind Kind)
	{
		switch (Kind)
		{
		case ENexusDocKind::Class:     return TEXT("CLASS");
		case ENexusDocKind::Component: return TEXT("COMP");
		case ENexusDocKind::Subsystem: return TEXT("SUB");
		case ENexusDocKind::Library:   return TEXT("LIB");
		case ENexusDocKind::Interface: return TEXT("IFACE");
		case ENexusDocKind::Actor:     return TEXT("ACTOR");
		case ENexusDocKind::Struct:    return TEXT("STRUCT");
		}
		return TEXT("?");
	}

	FString KindLongLabel(ENexusDocKind Kind)
	{
		switch (Kind)
		{
		case ENexusDocKind::Class:     return TEXT("Class");
		case ENexusDocKind::Component: return TEXT("Actor Component");
		case ENexusDocKind::Subsystem: return TEXT("Subsystem");
		case ENexusDocKind::Library:   return TEXT("Function Library");
		case ENexusDocKind::Interface: return TEXT("Interface");
		case ENexusDocKind::Actor:     return TEXT("Actor");
		case ENexusDocKind::Struct:    return TEXT("Struct");
		}
		return TEXT("Type");
	}

	TSharedPtr<FNexusDocClass> FindByTypeName(const FNexusDocCollection& Collection, const FString& TypeName)
	{
		if (TypeName.IsEmpty())
		{
			return nullptr;
		}
		// O(1) via the name cache when it's been built (it is, post-BuildFromNexusModule).
		if (const TSharedPtr<FNexusDocClass>* Found = Collection.ByName.Find(TypeName))
		{
			return *Found;
		}
		// Fallback scan (cache not yet populated, e.g. mid-build).
		for (const TSharedPtr<FNexusDocClass>& Entry : Collection.Classes)
		{
			if (Entry.IsValid() && Entry->TypeName == TypeName)
			{
				return Entry;
			}
		}
		return nullptr;
	}

	FNexusDocCollection BuildFromNexusModule()
	{
		FNexusDocCollection Collection;
		TSet<FString> CategorySet;

		for (TObjectIterator<UClass> It; It; ++It)
		{
			UClass* Class = *It;
			if (!IsInNexusModule(Class) || !ShouldIncludeClass(Class))
			{
				continue;
			}
			TSharedPtr<FNexusDocClass> Entry = MakeShared<FNexusDocClass>();
			PopulateClass(Class, *Entry);
			CategorySet.Add(Entry->Category);
			Collection.Classes.Add(MoveTemp(Entry));
		}

		for (TObjectIterator<UScriptStruct> It; It; ++It)
		{
			UScriptStruct* Struct = *It;
			if (!IsInNexusModule(Struct))
			{
				continue;
			}
			TSharedPtr<FNexusDocClass> Entry = MakeShared<FNexusDocClass>();
			PopulateStruct(Struct, *Entry);
			CategorySet.Add(Entry->Category);
			Collection.Classes.Add(MoveTemp(Entry));
		}

		Collection.Classes.Sort([](const TSharedPtr<FNexusDocClass>& A, const TSharedPtr<FNexusDocClass>& B)
		{
			if (A->Category != B->Category)
			{
				return A->Category < B->Category;
			}
			// Structs after classes within the same category.
			if (A->bIsStruct != B->bIsStruct)
			{
				return !A->bIsStruct;
			}
			return A->DisplayName < B->DisplayName;
		});

		Collection.Categories = CategorySet.Array();
		Collection.Categories.Sort();

		// Build the name cache before cross-referencing, so the Used-By / parent passes get
		// O(1) FindByTypeName instead of an O(N) scan per link.
		Collection.ByName.Reserve(Collection.Classes.Num());
		for (const TSharedPtr<FNexusDocClass>& Entry : Collection.Classes)
		{
			if (Entry.IsValid())
			{
				Collection.ByName.Add(Entry->TypeName, Entry);
			}
		}

		BuildCrossReferences(Collection);
		ComputeAggregateStats(Collection);
		return Collection;
	}
}
