#include "Misc/AutomationTest.h"

#include "Docs/NexusDocsModel.h"
#include "Docs/NexusMarkdown.h"

/**
 * Tests for the API-Reference back end: the reflection walker (NexusDocsModel),
 * the Markdown exporter, and the in-editor Markdown reader's inline transform.
 *
 * None of these touch Slate, so they pin down exactly the logic that used to be
 * impossible to verify without opening the tool by hand. Run from Tools → Test
 * Automation, or `Automation RunTests Nexus.Docs` on the command line.
 */

// =============================================================================
// Reflection walker invariants
// =============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNexusDocsModelInvariantsTest, "Nexus.Docs.ModelInvariants",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FNexusDocsModelInvariantsTest::RunTest(const FString& Parameters)
{
	const FNexusDocCollection Collection = NexusDocs::BuildFromNexusModule();

	// The aggregate counters must match a fresh recount of the per-type data.
	int32 RecountClasses = 0, RecountStructs = 0, RecountFunctions = 0;
	int32 RecountProps = 0, RecountEvents = 0, RecountDocumentedMembers = 0;
	for (const TSharedPtr<FNexusDocClass>& Entry : Collection.Classes)
	{
		TestTrue(TEXT("Every collection entry is valid"), Entry.IsValid());
		if (!Entry.IsValid())
		{
			continue;
		}
		if (Entry->bIsStruct) { ++RecountStructs; } else { ++RecountClasses; }
		RecountFunctions += Entry->Functions.Num();
		RecountProps += Entry->Properties.Num();
		RecountEvents += Entry->Events.Num();

		for (const FNexusDocFunction& Func : Entry->Functions) { if (Func.bHasDocs()) { ++RecountDocumentedMembers; } }
		for (const FNexusDocProperty& Prop : Entry->Properties) { if (Prop.bHasDocs()) { ++RecountDocumentedMembers; } }
		for (const FNexusDocProperty& Event : Entry->Events)    { if (Event.bHasDocs()) { ++RecountDocumentedMembers; } }

		// The name cache must round-trip every entry.
		TestTrue(*FString::Printf(TEXT("ByName resolves %s to itself"), *Entry->TypeName),
			Collection.ByName.FindRef(Entry->TypeName).Get() == Entry.Get());
	}

	TestEqual(TEXT("TotalClasses matches recount"), Collection.TotalClasses, RecountClasses);
	TestEqual(TEXT("TotalStructs matches recount"), Collection.TotalStructs, RecountStructs);
	TestEqual(TEXT("TotalFunctions matches recount"), Collection.TotalFunctions, RecountFunctions);
	TestEqual(TEXT("TotalProperties matches recount"), Collection.TotalProperties, RecountProps);
	TestEqual(TEXT("TotalEvents matches recount"), Collection.TotalEvents, RecountEvents);
	TestEqual(TEXT("TotalMembers is funcs + props + events"),
		Collection.TotalMembers, RecountFunctions + RecountProps + RecountEvents);
	TestEqual(TEXT("DocumentedMembers matches recount"), Collection.DocumentedMembers, RecountDocumentedMembers);

	// Coverage counters can never exceed their totals (drives the "% documented" band).
	TestTrue(TEXT("DocumentedMembers <= TotalMembers"), Collection.DocumentedMembers <= Collection.TotalMembers);
	TestTrue(TEXT("DocumentedClasses <= type count"),
		Collection.DocumentedClasses <= (Collection.TotalClasses + Collection.TotalStructs));

	// Categories are sorted and de-duplicated.
	for (int32 i = 1; i < Collection.Categories.Num(); ++i)
	{
		TestTrue(TEXT("Categories are strictly ascending (sorted, unique)"),
			Collection.Categories[i - 1] < Collection.Categories[i]);
	}

	// Lookups: empty / unknown names miss; a real type resolves to itself.
	TestNull(TEXT("Empty type name resolves to null"),
		NexusDocs::FindByTypeName(Collection, FString()).Get());
	TestNull(TEXT("Unknown type name resolves to null"),
		NexusDocs::FindByTypeName(Collection, TEXT("UThisIsNotARealNexusType_xyzzy")).Get());

	// Cross-reference symmetry: a derived link must point back to its parent.
	for (const TSharedPtr<FNexusDocClass>& Entry : Collection.Classes)
	{
		if (!Entry.IsValid())
		{
			continue;
		}
		for (const FString& DerivedName : Entry->DerivedTypeNames)
		{
			TSharedPtr<FNexusDocClass> Derived = NexusDocs::FindByTypeName(Collection, DerivedName);
			TestTrue(*FString::Printf(TEXT("Derived type %s is itself a Nexus type"), *DerivedName), Derived.IsValid());
			if (Derived.IsValid())
			{
				TestEqual(*FString::Printf(TEXT("%s lists %s as parent"), *DerivedName, *Entry->TypeName),
					Derived->ParentTypeName, Entry->TypeName);
			}
		}
	}

	return true;
}

// =============================================================================
// Kind labels
// =============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNexusDocsKindLabelsTest, "Nexus.Docs.KindLabels",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FNexusDocsKindLabelsTest::RunTest(const FString& Parameters)
{
	const ENexusDocKind Kinds[] = {
		ENexusDocKind::Class, ENexusDocKind::Component, ENexusDocKind::Subsystem,
		ENexusDocKind::Library, ENexusDocKind::Interface, ENexusDocKind::Actor, ENexusDocKind::Struct
	};
	for (ENexusDocKind Kind : Kinds)
	{
		TestFalse(TEXT("KindShortLabel is non-empty"), NexusDocs::KindShortLabel(Kind).IsEmpty());
		TestFalse(TEXT("KindLongLabel is non-empty"), NexusDocs::KindLongLabel(Kind).IsEmpty());
	}
	return true;
}

// =============================================================================
// Markdown export
// =============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNexusDocsExportTest, "Nexus.Docs.MarkdownExport",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FNexusDocsExportTest::RunTest(const FString& Parameters)
{
	const FNexusDocCollection Collection = NexusDocs::BuildFromNexusModule();
	const FString Markdown = NexusDocs::ExportMarkdown(Collection);

	TestTrue(TEXT("Export is non-empty"), !Markdown.IsEmpty());
	TestTrue(TEXT("Export opens with the reference title"), Markdown.StartsWith(TEXT("# Nexus API Reference")));

	// Every category should get an H2 section header in the document.
	for (const FString& Category : Collection.Categories)
	{
		TestTrue(*FString::Printf(TEXT("Export contains a '## %s' section"), *Category),
			Markdown.Contains(FString::Printf(TEXT("## %s"), *Category)));
	}

	return true;
}

// =============================================================================
// Markdown inline transform (the in-editor reader)
// =============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FNexusMarkdownInlineTest, "Nexus.Docs.MarkdownInline",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FNexusMarkdownInlineTest::RunTest(const FString& Parameters)
{
	using NexusMarkdown::ToSlateMarkup;

	// Plain prose becomes a single Normal run.
	TestEqual(TEXT("Plain text -> one Normal run"),
		ToSlateMarkup(TEXT("hello")), FString(TEXT("<RichText.Normal>hello</>")));

	// Bold and code rewrites.
	TestTrue(TEXT("** ** becomes a Bold run"),
		ToSlateMarkup(TEXT("**x**")).Contains(TEXT("<RichText.Bold>x</>")));
	TestTrue(TEXT("backticks become a Code run"),
		ToSlateMarkup(TEXT("`x`")).Contains(TEXT("<RichText.Code>x</>")));

	// Markup-significant characters inside code are escaped, not dropped.
	{
		const FString Out = ToSlateMarkup(TEXT("`TMap<A,B>`"));
		TestTrue(TEXT("'<' inside code is escaped"), Out.Contains(TEXT("&lt;")));
		TestTrue(TEXT("'>' inside code is escaped"), Out.Contains(TEXT("&gt;")));
		TestFalse(TEXT("no raw '<' leaks into markup"), Out.Contains(TEXT("<A")));
	}

	// Ampersands in prose are escaped (Attachment & Weapon...).
	TestTrue(TEXT("'&' is escaped"), ToSlateMarkup(TEXT("a & b")).Contains(TEXT("&amp;")));

	// Underscores are identifiers, never emphasis.
	{
		const FString Out = ToSlateMarkup(TEXT("Fragment_Weapon"));
		TestFalse(TEXT("underscore does not open italic"), Out.Contains(TEXT("<RichText.Italic>")));
		TestTrue(TEXT("identifier text survives"), Out.Contains(TEXT("Fragment_Weapon")));
	}

	// A lone asterisk in prose ("a * b") is not emphasis (flanking guard).
	{
		const FString Out = ToSlateMarkup(TEXT("a * b"));
		TestFalse(TEXT("lone '*' does not open italic"), Out.Contains(TEXT("<RichText.Italic>")));
	}

	// Interleaved bold + code splits into two flat runs (Slate runs can't nest).
	{
		const FString Out = ToSlateMarkup(TEXT("**Lyra `Foo`**"));
		TestTrue(TEXT("bold prefix run"), Out.Contains(TEXT("<RichText.Bold>Lyra </>")));
		TestTrue(TEXT("code run inside the bold span"), Out.Contains(TEXT("<RichText.Code>Foo</>")));
	}

	// Empty input yields empty markup.
	TestEqual(TEXT("Empty input -> empty output"), ToSlateMarkup(FString()), FString());

	return true;
}
