#pragma once

#include "CoreMinimal.h"
#include "Templates/SharedPointer.h"

class ISlateStyle;
class SWidget;

/**
 * Small, dependency-light Markdown renderer for the Nexus API Reference's
 * in-editor reader. The architecture docs under <Project>/Docs only use a
 * narrow subset of Markdown — ATX headings (#/##/###), ordered and unordered
 * lists (with one level of nesting), blockquotes, fenced code, horizontal
 * rules, paragraphs, and inline **bold** / *italic* / `code` / ~~strike~~ /
 * [text](url) — so a full CommonMark parser would be wasted weight. This
 * renderer covers exactly that subset and degrades gracefully on anything it
 * doesn't recognise (unknown syntax falls through as plain text, never a
 * crash).
 *
 * Two layers, split so the fiddly bit can be pinned down by tests:
 *
 *  - ToSlateMarkup() is a PURE string transform (Markdown inline syntax ->
 *    Slate rich-text run markup). It is unit-tested in NexusDocsModelTests.
 *  - BuildDocument() is the block-level pass: it walks lines, groups them into
 *    block elements, and returns a stacked Slate widget tree. Text that can
 *    carry inline styling is rendered with SRichTextBlock against Style().
 */
namespace NexusMarkdown
{
	/**
	 * Convert one line / paragraph of Markdown inline syntax into the rich-text
	 * run markup understood by SRichTextBlock together with Style(). The three
	 * markup-significant characters (& < >) are escaped first — so code such as
	 * `TMap<FKey, FValue>` survives intact — then **bold**, *italic*, `code`,
	 * ~~strike~~, and [text](url) are rewritten into <RichText.*>...</> runs.
	 * Emphasis markers use light flanking rules so prose like "a * b" or an
	 * identifier such as Fragment_Weapon is left untouched.
	 */
	FString ToSlateMarkup(const FString& InlineSource);

	/** Shared, lazily-built text-style set that backs the <RichText.*> run names. */
	const ISlateStyle& Style();

	/**
	 * Parse a whole Markdown document into a vertical stack of Slate widgets
	 * (headings, ordered / unordered lists, blockquotes, fenced code, rules,
	 * paragraphs). Safe to call with arbitrary text; never returns null.
	 */
	TSharedRef<SWidget> BuildDocument(const FString& Markdown);
}
