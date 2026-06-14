#include "Docs/NexusMarkdown.h"

#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"
#include "Styling/SlateColor.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateTypes.h"
#include "Styling/StyleColors.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Text/SRichTextBlock.h"
#include "Widgets/Text/STextBlock.h"

namespace
{
	// ---------------------------------------------------------------------------
	// Inline pass
	// ---------------------------------------------------------------------------

	/** Treat tab, space, and end-of-string as "whitespace" for flanking checks. */
	FORCEINLINE bool IsInlineSpace(TCHAR Ch)
	{
		return Ch == TEXT(' ') || Ch == TEXT('\t') || Ch == TEXT('\0');
	}

	/**
	 * Escape the three characters Slate's rich-text markup parser treats as
	 * structural. Order matters: '&' first, so the ampersands introduced by the
	 * '<' and '>' replacements aren't double-escaped.
	 */
	FString EscapeRich(const FString& In)
	{
		FString Out = In;
		Out.ReplaceInline(TEXT("&"), TEXT("&amp;"), ESearchCase::CaseSensitive);
		Out.ReplaceInline(TEXT("<"), TEXT("&lt;"), ESearchCase::CaseSensitive);
		Out.ReplaceInline(TEXT(">"), TEXT("&gt;"), ESearchCase::CaseSensitive);
		return Out;
	}

	TSharedPtr<FSlateStyleSet> GMarkdownStyle;

	FTextBlockStyle MakeTextStyle(const ANSICHAR* FontStyle, int32 Size, const FSlateColor& Color)
	{
		return FTextBlockStyle()
			.SetFont(FCoreStyle::GetDefaultFontStyle(FontStyle, Size))
			.SetColorAndOpacity(Color);
	}
}

namespace NexusMarkdown
{
	FString ToSlateMarkup(const FString& Source)
	{
		FString Out;
		Out.Reserve(Source.Len() + 32);

		// Text accumulated for the run currently open; escaped only at flush time
		// so the markup-significant characters are handled in exactly one place.
		FString Pending;

		bool bBold = false;
		bool bItalic = false;
		bool bCode = false;
		bool bStrike = false;

		auto CurrentRunStyle = [&]() -> const TCHAR*
		{
			// Code wins (inside a code span nothing else applies); otherwise the
			// strongest active emphasis. Slate runs are flat, so a single run can
			// only carry one style — this precedence keeps interleaving readable.
			if (bCode)   { return TEXT("RichText.Code"); }
			if (bBold)   { return TEXT("RichText.Bold"); }
			if (bStrike) { return TEXT("RichText.Strike"); }
			if (bItalic) { return TEXT("RichText.Italic"); }
			return TEXT("RichText.Normal");
		};

		auto Flush = [&]()
		{
			if (Pending.IsEmpty())
			{
				return;
			}
			Out += FString::Printf(TEXT("<%s>%s</>"), CurrentRunStyle(), *EscapeRich(Pending));
			Pending.Reset();
		};

		const int32 Len = Source.Len();
		for (int32 i = 0; i < Len; )
		{
			const TCHAR C = Source[i];
			const TCHAR N = (i + 1 < Len) ? Source[i + 1] : TEXT('\0');
			const TCHAR P = (i > 0) ? Source[i - 1] : TEXT('\0');

			// Inside a code span only a backtick is special; everything else is literal.
			if (bCode)
			{
				if (C == TEXT('`')) { Flush(); bCode = false; ++i; continue; }
				Pending.AppendChar(C); ++i; continue;
			}

			if (C == TEXT('`'))
			{
				Flush();
				bCode = true;
				++i;
				continue;
			}

			// Bold (**). Open only when the next char isn't whitespace; close only
			// when the previous char wasn't whitespace — otherwise treat literally.
			if (C == TEXT('*') && N == TEXT('*'))
			{
				const TCHAR AfterDelim = (i + 2 < Len) ? Source[i + 2] : TEXT('\0');
				const bool bCanOpen  = !bBold && !IsInlineSpace(AfterDelim);
				const bool bCanClose =  bBold && !IsInlineSpace(P);
				if (bCanOpen || bCanClose)
				{
					Flush();
					bBold = !bBold;
					i += 2;
					continue;
				}
				Pending.Append(TEXT("**"));
				i += 2;
				continue;
			}

			// Strikethrough (~~) — same flanking rule.
			if (C == TEXT('~') && N == TEXT('~'))
			{
				const TCHAR AfterDelim = (i + 2 < Len) ? Source[i + 2] : TEXT('\0');
				const bool bCanOpen  = !bStrike && !IsInlineSpace(AfterDelim);
				const bool bCanClose =  bStrike && !IsInlineSpace(P);
				if (bCanOpen || bCanClose)
				{
					Flush();
					bStrike = !bStrike;
					i += 2;
					continue;
				}
				Pending.Append(TEXT("~~"));
				i += 2;
				continue;
			}

			// Italic (single *). Underscores are deliberately NOT emphasis — they
			// appear constantly in identifiers (Fragment_Weapon, IA_Fire).
			if (C == TEXT('*'))
			{
				const bool bCanOpen  = !bItalic && !IsInlineSpace(N);
				const bool bCanClose =  bItalic && !IsInlineSpace(P);
				if (bCanOpen || bCanClose)
				{
					Flush();
					bItalic = !bItalic;
					++i;
					continue;
				}
				Pending.AppendChar(C);
				++i;
				continue;
			}

			// Link [text](url) — render the text in link colour, drop the URL
			// (the inline reader can't navigate, and the docs rarely use links).
			if (C == TEXT('['))
			{
				int32 CloseBracket = INDEX_NONE;
				for (int32 k = i + 1; k < Len; ++k)
				{
					if (Source[k] == TEXT(']')) { CloseBracket = k; break; }
				}
				if (CloseBracket != INDEX_NONE && CloseBracket + 1 < Len && Source[CloseBracket + 1] == TEXT('('))
				{
					int32 CloseParen = INDEX_NONE;
					for (int32 k = CloseBracket + 2; k < Len; ++k)
					{
						if (Source[k] == TEXT(')')) { CloseParen = k; break; }
					}
					if (CloseParen != INDEX_NONE)
					{
						Flush();
						const FString LinkText = Source.Mid(i + 1, CloseBracket - i - 1);
						Out += FString::Printf(TEXT("<RichText.Link>%s</>"), *EscapeRich(LinkText));
						i = CloseParen + 1;
						continue;
					}
				}
				Pending.AppendChar(C);
				++i;
				continue;
			}

			Pending.AppendChar(C);
			++i;
		}

		Flush();
		return Out;
	}

	const ISlateStyle& Style()
	{
		if (!GMarkdownStyle.IsValid())
		{
			TSharedRef<FSlateStyleSet> Set = MakeShared<FSlateStyleSet>("NexusMarkdown");

			const FSlateColor Body     = FSlateColor::UseForeground();
			const FSlateColor Subdued  = FSlateColor::UseSubduedForeground();
			const FSlateColor CodeTint = FSlateColor(FStyleColors::AccentYellow);
			const FSlateColor LinkTint = FSlateColor(FStyleColors::AccentBlue);

			Set->Set("RichText.Normal", MakeTextStyle("Regular", 10, Body));
			Set->Set("RichText.Bold",   MakeTextStyle("Bold",    10, Body));
			Set->Set("RichText.Italic", MakeTextStyle("Italic",  10, Body));
			Set->Set("RichText.Code",   MakeTextStyle("Mono",    10, CodeTint));
			Set->Set("RichText.Strike", MakeTextStyle("Italic",  10, Subdued));
			Set->Set("RichText.Link",   MakeTextStyle("Regular", 10, LinkTint));

			GMarkdownStyle = Set;
		}
		return *GMarkdownStyle;
	}

	// ---------------------------------------------------------------------------
	// Block pass
	// ---------------------------------------------------------------------------

	TSharedRef<SWidget> BuildDocument(const FString& Markdown)
	{
		TSharedRef<SVerticalBox> Body = SNew(SVerticalBox);

		// One rich-text paragraph/list-item/quote, run through the inline pass.
		auto MakeRich = [](const FString& InlineText) -> TSharedRef<SWidget>
		{
			return SNew(SRichTextBlock)
				.Text(FText::FromString(ToSlateMarkup(InlineText)))
				.TextStyle(&Style().GetWidgetStyle<FTextBlockStyle>("RichText.Normal"))
				.DecoratorStyleSet(&Style())
				.AutoWrapText(true);
		};

		TArray<FString> Lines;
		Markdown.ParseIntoArrayLines(Lines, /*bCullEmpty=*/false);

		FString CurrentParagraph;
		TArray<FString> CurrentCodeLines;
		bool bInCodeBlock = false;

		auto FlushParagraph = [&Body, &CurrentParagraph, &MakeRich]()
		{
			if (CurrentParagraph.IsEmpty()) { return; }
			Body->AddSlot()
				.AutoHeight()
				.Padding(0.0f, 4.0f, 0.0f, 6.0f)
				[
					MakeRich(CurrentParagraph)
				];
			CurrentParagraph.Reset();
		};

		auto FlushCodeBlock = [&Body, &CurrentCodeLines]()
		{
			if (CurrentCodeLines.Num() == 0) { return; }
			const FString Joined = FString::Join(CurrentCodeLines, TEXT("\n"));
			Body->AddSlot()
				.AutoHeight()
				.Padding(0.0f, 6.0f, 0.0f, 6.0f)
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
					.Padding(FMargin(12.0f, 8.0f))
					[
						SNew(STextBlock)
						.Text(FText::FromString(Joined))
						.Font(FCoreStyle::GetDefaultFontStyle("Mono", 10))
						.AutoWrapText(true)
					]
				];
			CurrentCodeLines.Reset();
		};

		// Indentation (in leading spaces, tabs counted as 4) -> left padding, so
		// nested lists step inward instead of all collapsing to the same margin.
		auto LeadingIndent = [](const FString& Raw) -> int32
		{
			int32 Spaces = 0;
			for (int32 k = 0; k < Raw.Len(); ++k)
			{
				if (Raw[k] == TEXT(' '))      { ++Spaces; }
				else if (Raw[k] == TEXT('\t')) { Spaces += 4; }
				else { break; }
			}
			return Spaces;
		};

		auto IsHeading = [](const FString& Line, int32 Level) -> bool
		{
			if (Line.Len() < Level + 1) { return false; }
			for (int32 h = 0; h < Level; ++h) { if (Line[h] != TEXT('#')) { return false; } }
			return Line[Level] == TEXT(' ');
		};

		auto AddHeading = [&Body](const FString& Text, int32 FontSize, float TopPad)
		{
			Body->AddSlot()
				.AutoHeight()
				.Padding(0.0f, TopPad, 0.0f, 4.0f)
				[
					SNew(STextBlock)
					.Text(FText::FromString(Text))
					.Font(FCoreStyle::GetDefaultFontStyle("Bold", FontSize))
					.AutoWrapText(true)
				];
		};

		for (const FString& RawLine : Lines)
		{
			FString Trimmed = RawLine;
			Trimmed.TrimStartInline();

			// Fenced code blocks (```), language tag ignored.
			if (Trimmed.StartsWith(TEXT("```")))
			{
				if (bInCodeBlock) { FlushCodeBlock(); bInCodeBlock = false; }
				else              { FlushParagraph(); bInCodeBlock = true; }
				continue;
			}
			if (bInCodeBlock)
			{
				CurrentCodeLines.Add(RawLine);
				continue;
			}

			// Blank line ends a paragraph.
			if (Trimmed.IsEmpty())
			{
				FlushParagraph();
				continue;
			}

			// Horizontal rule.
			if (Trimmed == TEXT("---") || Trimmed == TEXT("***") || Trimmed == TEXT("___"))
			{
				FlushParagraph();
				Body->AddSlot()
					.AutoHeight()
					.Padding(0.0f, 10.0f, 0.0f, 10.0f)
					[
						SNew(SSeparator).Orientation(Orient_Horizontal).Thickness(1.0f)
					];
				continue;
			}

			// Headings — deepest first so "###" isn't matched as "#".
			if (IsHeading(Trimmed, 3)) { FlushParagraph(); AddHeading(Trimmed.RightChop(4), 11, 14.0f); continue; }
			if (IsHeading(Trimmed, 2)) { FlushParagraph(); AddHeading(Trimmed.RightChop(3), 14, 18.0f); continue; }
			if (IsHeading(Trimmed, 1)) { FlushParagraph(); AddHeading(Trimmed.RightChop(2), 18, 20.0f); continue; }

			const int32 IndentPx = 20 + (LeadingIndent(RawLine) / 2) * 16;

			// Ordered list — "1. ", "2. ", ... Keep the author's number.
			{
				int32 Digits = 0;
				while (Digits < Trimmed.Len() && FChar::IsDigit(Trimmed[Digits])) { ++Digits; }
				if (Digits > 0 && Digits + 1 < Trimmed.Len()
					&& Trimmed[Digits] == TEXT('.') && Trimmed[Digits + 1] == TEXT(' '))
				{
					FlushParagraph();
					const FString Marker = Trimmed.Left(Digits + 1);      // "1."
					const FString ItemText = Trimmed.RightChop(Digits + 2);
					Body->AddSlot()
						.AutoHeight()
						.Padding(static_cast<float>(IndentPx), 2.0f, 0.0f, 2.0f)
						[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot()
							.AutoWidth()
							.VAlign(VAlign_Top)
							.Padding(0.0f, 0.0f, 6.0f, 0.0f)
							[
								SNew(SBox).MinDesiredWidth(20.0f)
								[
									SNew(STextBlock)
									.Text(FText::FromString(Marker))
									.Font(FCoreStyle::GetDefaultFontStyle("Bold", 10))
								]
							]
							+ SHorizontalBox::Slot().FillWidth(1.0f)[ MakeRich(ItemText) ]
						];
					continue;
				}
			}

			// Unordered list — "- ", "* ", "+ ".
			if (Trimmed.StartsWith(TEXT("- ")) || Trimmed.StartsWith(TEXT("* ")) || Trimmed.StartsWith(TEXT("+ ")))
			{
				FlushParagraph();
				Body->AddSlot()
					.AutoHeight()
					.Padding(static_cast<float>(IndentPx), 2.0f, 0.0f, 2.0f)
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.VAlign(VAlign_Top)
						.Padding(0.0f, 0.0f, 6.0f, 0.0f)
						[
							SNew(STextBlock).Text(FText::FromString(TEXT("•")))
						]
						+ SHorizontalBox::Slot().FillWidth(1.0f)[ MakeRich(Trimmed.RightChop(2)) ]
					];
				continue;
			}

			// Block quote — "> ".
			if (Trimmed.StartsWith(TEXT("> ")) || Trimmed == TEXT(">"))
			{
				FlushParagraph();
				const FString QuoteText = Trimmed.StartsWith(TEXT("> ")) ? Trimmed.RightChop(2) : FString();
				Body->AddSlot()
					.AutoHeight()
					.Padding(0.0f, 6.0f, 0.0f, 6.0f)
					[
						SNew(SBorder)
						.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
						.Padding(FMargin(14.0f, 8.0f))
						[
							SNew(SRichTextBlock)
							.Text(FText::FromString(ToSlateMarkup(QuoteText)))
							.TextStyle(&Style().GetWidgetStyle<FTextBlockStyle>("RichText.Italic"))
							.DecoratorStyleSet(&Style())
							.AutoWrapText(true)
						]
					];
				continue;
			}

			// Default: accumulate as paragraph text. Soft-wrapped lines join with a
			// space so the renderer's own word-wrap takes over.
			if (!CurrentParagraph.IsEmpty())
			{
				CurrentParagraph.AppendChar(TEXT(' '));
			}
			CurrentParagraph.Append(Trimmed);
		}

		FlushParagraph();
		if (bInCodeBlock)
		{
			FlushCodeBlock();
		}

		return Body;
	}
}
