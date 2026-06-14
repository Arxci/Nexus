#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SBox;
class FNexusAssetWatcher;

/**
 * Cross-asset content insights for the survival-horror content set, in one tool with modes:
 *
 *   Reachability — items the player can never obtain (not in any manifest and not craftable
 *                  from reachable inputs) — the soft-lock catcher (transitive over recipes).
 *   Scarcity     — supply census: how many of each category are placed across all manifests.
 *   Localization — items/attachments missing a DisplayName or Description.
 *   Where-Used   — which manifests place each item (flags items placed nowhere).
 *   Builds       — attachments that can never be installed (unsatisfied required tags).
 *
 * Read-only; clicking an asset selects it for the Inspector. Live-refreshes on content change.
 */
class SNexusContentInsights : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SNexusContentInsights) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	enum class EMode : uint8 { Reachability, Scarcity, Localization, WhereUsed, Builds };

	void SetMode(EMode NewMode);
	void Refresh();
	TSharedRef<SWidget> BuildPanel();
	TSharedRef<SWidget> BuildReachability();
	TSharedRef<SWidget> BuildScarcity();
	TSharedRef<SWidget> BuildLocalization();
	TSharedRef<SWidget> BuildWhereUsed();
	TSharedRef<SWidget> BuildBuilds();

	EMode Mode = EMode::Reachability;
	TSharedPtr<SBox> ContentHost;
	FText SummaryText;
	TSharedPtr<FNexusAssetWatcher> Watcher;
};
