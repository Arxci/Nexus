#include "Live/SNexusLiveInventory.h"

#include "NexusEditorModule.h"
#include "Sandbox/SNexusInventoryCanvas.h"
#include "Shared/NexusEditorAssetWatcher.h"
#include "Shared/NexusEditorStyle.h"
#include "Shared/NexusEditorUtils.h"
#include "Shared/NexusEditorWidgets.h"

#include "Editor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/Pawn.h"

#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"

#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSplitter.h"
#include "Widgets/Text/STextBlock.h"

#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusInventoryAcquireLibrary.h"
#include "Nexus/Inventory/NexusItemContainer.h"
#include "Nexus/Inventory/NexusItemContainerSubsystem.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"

#define LOCTEXT_NAMESPACE "NexusLiveInventory"

namespace
{
	const FName GLiveInventorySource(TEXT("NexusLiveInventory"));

	uint32 NexusPtrHash(const void* Ptr)
	{
		return GetTypeHash(reinterpret_cast<UPTRINT>(Ptr));
	}
}

// --- Live-world location ------------------------------------------------------------------

UWorld* SNexusLiveInventory::GetPIEWorld() const
{
	return (GEditor && GEditor->PlayWorld) ? GEditor->PlayWorld : nullptr;
}

APawn* SNexusLiveInventory::GetPlayerPawn() const
{
	UWorld* World = GetPIEWorld();
	return World ? UGameplayStatics::GetPlayerPawn(World, 0) : nullptr;
}

UNexusInventoryComponent* SNexusLiveInventory::GetPlayerInventory() const
{
	APawn* Pawn = GetPlayerPawn();
	return Pawn ? Pawn->FindComponentByClass<UNexusInventoryComponent>() : nullptr;
}

UNexusItemContainerSubsystem* SNexusLiveInventory::GetBoxSubsystem() const
{
	UWorld* World = GetPIEWorld();
	return World ? UNexusItemContainerSubsystem::Get(World) : nullptr;
}

bool SNexusLiveInventory::IsLive() const
{
	return GetPlayerInventory() != nullptr;
}

// --- Construct ----------------------------------------------------------------------------

void SNexusLiveInventory::Construct(const FArguments& InArgs)
{
	SAssignNew(Canvas, SNexusInventoryCanvas);
	Canvas->SetReadOnly(true);
	Canvas->SetOnItemClicked([](UNexusItemDefinition* Def)
	{
		if (Def)
		{
			FNexusEditorModule::SetSelection(Def, GLiveInventorySource);
		}
	});

	SAssignNew(SidePanel, SVerticalBox);
	SAssignNew(BoxList, SVerticalBox);

	PlayerCaseBody =
		SNew(SSplitter)
		+ SSplitter::Slot().Value(0.68f)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
			.Padding(6.0f)
			[
				SNew(SScrollBox)
				+ SScrollBox::Slot()[ Canvas.ToSharedRef() ]
			]
		]
		+ SSplitter::Slot().Value(0.32f)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
			.Padding(6.0f)
			[
				SNew(SScrollBox)
				+ SScrollBox::Slot()[ SidePanel.ToSharedRef() ]
			]
		];

	ItemBoxBody =
		SNew(SBorder)
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Recessed"))
		.Padding(6.0f)
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()[ BoxList.ToSharedRef() ]
		];

	RebuildPickLists();

	const auto ViewButton = [this](EView Which, const FText& Label) -> TSharedRef<SWidget>
	{
		return SNew(SCheckBox)
			.Style(FAppStyle::Get(), "DetailsView.SectionButton")
			.Padding(FMargin(12.0f, 3.0f))
			.IsChecked_Lambda([this, Which]() { return View == Which ? ECheckBoxState::Checked : ECheckBoxState::Unchecked; })
			.OnCheckStateChanged_Lambda([this, Which](ECheckBoxState S) { if (S == ECheckBoxState::Checked) { SetView(Which); } })
			[ SNew(STextBlock).Text(Label) ];
	};

	const auto MutationButton = [this](const FText& Label, const FText& Tip, FReply (SNexusLiveInventory::*Handler)(), TFunction<bool()> Enabled) -> TSharedRef<SWidget>
	{
		return SNew(SButton)
			.Text(Label)
			.ToolTipText(Tip)
			.IsEnabled_Lambda([Enabled]() { return Enabled(); })
			.OnClicked(FOnClicked::CreateSP(this, Handler));
	};

	ChildSlot
	[
		SNew(SVerticalBox)

		// Toolbar: view toggle + live status.
		+ SVerticalBox::Slot().AutoHeight()
		[
			NexusEditorWidgets::Toolbar(
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)[ ViewButton(EView::PlayerCase, LOCTEXT("Case", "Player Case")) ]
				+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)[ ViewButton(EView::ItemBox, LOCTEXT("Box", "Item Box")) ]
				+ SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center).Padding(12.0f, 0.0f, 0.0f, 0.0f)
				[
					SNew(STextBlock)
					.Text_Lambda([this]() { return GetStatusText(); })
					.ColorAndOpacity_Lambda([this]() { return IsLive() ? NexusEditorStyle::Valid() : FSlateColor::UseSubduedForeground(); })
				]
			)
		]

		// Body: live grid (case) or contents list (box).
		+ SVerticalBox::Slot().FillHeight(1.0f).Padding(8.0f)
		[
			SAssignNew(BodyHost, SBox)
		]

		// Mutations — gated on a live PIE world; everything goes through the runtime public API.
		+ SVerticalBox::Slot().AutoHeight()
		[
			NexusEditorWidgets::Toolbar(
				SNew(SVerticalBox)
				+ SVerticalBox::Slot().AutoHeight().Padding(0.0f, 0.0f, 0.0f, 4.0f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center)
					[
						SAssignNew(SpawnCombo, SComboBox<TSharedPtr<FPick>>)
						.OptionsSource(&SpawnOptions)
						.OnGenerateWidget_Lambda([](TSharedPtr<FPick> P) { return SNew(STextBlock).Text(FText::FromString(P.IsValid() ? P->Label : FString())); })
						.OnSelectionChanged_Lambda([this](TSharedPtr<FPick> P, ESelectInfo::Type) { SelectedSpawn = P; })
						.InitiallySelectedItem(SelectedSpawn)
						[
							SNew(STextBlock).Text_Lambda([this]()
							{
								return SelectedSpawn.IsValid() ? FText::FromString(SelectedSpawn->Label) : LOCTEXT("PickItem", "Pick an item…");
							})
						]
					]
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(6.0f, 0.0f)
					[
						SNew(SBox).WidthOverride(64.0f)
						[
							SNew(SSpinBox<int32>)
							.MinValue(1).MaxValue(999)
							.Value_Lambda([this]() { return SpawnCount; })
							.OnValueChanged_Lambda([this](int32 V) { SpawnCount = FMath::Max(1, V); })
						]
					]
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
					[
						MutationButton(LOCTEXT("Spawn", "Spawn"), LOCTEXT("SpawnTip", "Give the selected item to the player (AcquireItem, no ceremony)."),
							&SNexusLiveInventory::OnSpawnClicked, [this]() { return IsLive() && SelectedSpawn.IsValid(); })
					]
				]
				+ SVerticalBox::Slot().AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot().FillWidth(1.0f).VAlign(VAlign_Center)
					[
						SAssignNew(CaseCombo, SComboBox<TSharedPtr<FPick>>)
						.OptionsSource(&CaseOptions)
						.OnGenerateWidget_Lambda([](TSharedPtr<FPick> P) { return SNew(STextBlock).Text(FText::FromString(P.IsValid() ? P->Label : FString())); })
						.OnSelectionChanged_Lambda([this](TSharedPtr<FPick> P, ESelectInfo::Type) { SelectedCase = P; })
						.InitiallySelectedItem(SelectedCase)
						[
							SNew(STextBlock).Text_Lambda([this]()
							{
								return SelectedCase.IsValid() ? FText::FromString(SelectedCase->Label) : LOCTEXT("PickCase", "Pick a case…");
							})
						]
					]
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(6.0f, 0.0f, 0.0f, 0.0f)
					[
						MutationButton(LOCTEXT("SwapCase", "Swap Case"), LOCTEXT("SwapCaseTip", "Equip the selected case; items that no longer fit spill to the item box."),
							&SNexusLiveInventory::OnSwapCaseClicked, [this]() { return IsLive() && SelectedCase.IsValid() && GetBoxSubsystem() != nullptr; })
					]
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(12.0f, 0.0f, 0.0f, 0.0f)
					[
						MutationButton(LOCTEXT("AutoArrange", "Auto-arrange"), LOCTEXT("AutoArrangeTip", "Repack the spatial grid (the in-game Optimize)."),
							&SNexusLiveInventory::OnAutoArrangeClicked, [this]() { return IsLive(); })
					]
					+ SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center).Padding(6.0f, 0.0f, 0.0f, 0.0f)
					[
						MutationButton(LOCTEXT("Clear", "Clear"), LOCTEXT("ClearTip", "Remove every item from the player inventory."),
							&SNexusLiveInventory::OnClearClicked, [this]() { return IsLive(); })
					]
				]
				+ SVerticalBox::Slot().AutoHeight().Padding(0.0f, 4.0f, 0.0f, 0.0f)
				[
					SNew(STextBlock)
					.Text_Lambda([this]() { return LastActionResult; })
					.ColorAndOpacity(FSlateColor::UseSubduedForeground())
					.AutoWrapText(true)
				]
			)
		]
	];

	SetView(EView::PlayerCase);

	// Poll the live world a few times a second; cheap, and robust to PIE start/stop and teardown.
	RegisterActiveTimer(0.3f, FWidgetActiveTimerDelegate::CreateSP(this, &SNexusLiveInventory::ActiveTick));

	// Keep the spawn / case pickers fresh as content is authored.
	Watcher = MakeShared<FNexusAssetWatcher>();
	Watcher->Start({ UNexusItemDefinition::StaticClass() }, [this]() { RebuildPickLists(); });
}

// --- Refresh ------------------------------------------------------------------------------

EActiveTimerReturnType SNexusLiveInventory::ActiveTick(double, float)
{
	RefreshLive();
	return EActiveTimerReturnType::Continue;
}

uint32 SNexusLiveInventory::ComputeSignature() const
{
	uint32 Hash = GetTypeHash(static_cast<uint8>(View));
	Hash = HashCombine(Hash, IsLive() ? 1u : 0u);

	if (View == EView::PlayerCase)
	{
		if (UNexusInventoryComponent* Inventory = GetPlayerInventory())
		{
			Hash = HashCombine(Hash, GetTypeHash(Inventory->GetGridSize()));
			for (UNexusItemInstance* Instance : Inventory->GetItems())
			{
				if (!Instance) { continue; }
				Hash = HashCombine(Hash, NexusPtrHash(Instance->GetDefinition()));
				Hash = HashCombine(Hash, GetTypeHash(Instance->GetGridPosition()));
				Hash = HashCombine(Hash, Instance->IsRotated() ? 2u : 1u);
				Hash = HashCombine(Hash, static_cast<uint32>(Instance->GetStackCount()));
			}
			Hash = HashCombine(Hash, NexusPtrHash(Inventory->GetEquippedCaseDefinition()));
			for (const FGameplayTag& Slot : Inventory->GetCaseCharmSlots())
			{
				Hash = HashCombine(Hash, GetTypeHash(Slot));
				Hash = HashCombine(Hash, NexusPtrHash(Inventory->GetSocketedCharm(Slot)));
			}
		}
	}
	else
	{
		if (UNexusItemContainerSubsystem* Box = GetBoxSubsystem())
		{
			Hash = HashCombine(Hash, static_cast<uint32>(Box->GetCurrency()));
			if (UNexusItemContainer* Container = Box->GetBox())
			{
				for (UNexusItemInstance* Instance : Container->GetItems())
				{
					if (!Instance) { continue; }
					Hash = HashCombine(Hash, NexusPtrHash(Instance->GetDefinition()));
					Hash = HashCombine(Hash, static_cast<uint32>(Instance->GetStackCount()));
				}
			}
		}
	}
	return Hash;
}

void SNexusLiveInventory::RefreshLive()
{
	const uint32 Signature = ComputeSignature();
	if (!bForceRefresh && Signature == LastSignature)
	{
		return;
	}
	bForceRefresh = false;
	LastSignature = Signature;

	if (View == EView::PlayerCase)
	{
		RefreshPlayerCase();
	}
	else
	{
		RefreshItemBox();
	}
}

void SNexusLiveInventory::SetView(EView InView)
{
	View = InView;
	if (BodyHost.IsValid())
	{
		BodyHost->SetContent(View == EView::PlayerCase ? PlayerCaseBody.ToSharedRef() : ItemBoxBody.ToSharedRef());
	}
	bForceRefresh = true;
	RefreshLive();
}

void SNexusLiveInventory::RefreshPlayerCase()
{
	UNexusInventoryComponent* Inventory = GetPlayerInventory();
	if (!Inventory)
	{
		if (Canvas.IsValid())
		{
			Canvas->MirrorSpatialItems(1, 1, TArray<FNexusItemSaveData>());
		}
		PopulateSidePanel(nullptr);
		return;
	}

	// Snapshot only the grid-placed items; off-grid (Key Items / Treasures / overflow) are
	// listed in the side panel instead.
	TArray<FNexusItemSaveData> Spatial;
	for (UNexusItemInstance* Instance : Inventory->GetItems())
	{
		if (Instance && Instance->GetGridPosition() != FIntPoint(-1, -1))
		{
			Spatial.Add(Instance->ToSaveData());
		}
	}

	const FIntPoint Grid = Inventory->GetGridSize();
	if (Canvas.IsValid())
	{
		Canvas->MirrorSpatialItems(Grid.X, Grid.Y, Spatial);
	}
	PopulateSidePanel(Inventory);
}

void SNexusLiveInventory::PopulateSidePanel(UNexusInventoryComponent* Inventory)
{
	if (!SidePanel.IsValid())
	{
		return;
	}
	SidePanel->ClearChildren();

	const FSlateFontInfo BoldFont = FCoreStyle::GetDefaultFontStyle("Bold", 9);

	auto AddHeader = [this, BoldFont](const FString& Text)
	{
		SidePanel->AddSlot().AutoHeight().Padding(2.0f, 8.0f, 2.0f, 2.0f)
		[ SNew(STextBlock).Text(FText::FromString(Text)).Font(BoldFont) ];
	};
	auto AddLine = [this](const FString& Text, FSlateColor Color = FSlateColor::UseForeground())
	{
		SidePanel->AddSlot().AutoHeight().Padding(2.0f, 1.0f)
		[ SNew(STextBlock).Text(FText::FromString(Text)).ColorAndOpacity(Color).AutoWrapText(true) ];
	};

	if (!Inventory)
	{
		AddLine(TEXT("No live player inventory. Start Play-In-Editor to inspect the real container."),
			FSlateColor::UseSubduedForeground());
		return;
	}

	AddHeader(TEXT("CAPACITY"));
	const FIntPoint Grid = Inventory->GetGridSize();
	AddLine(FString::Printf(TEXT("Grid: %d x %d cells"), Grid.X, Grid.Y));
	if (Canvas.IsValid())
	{
		AddLine(FString::Printf(TEXT("Cells used: %d / %d"), Canvas->GetUsedCellCount(), Canvas->GetTotalCellCount()));
	}
	AddLine(FString::Printf(TEXT("Stacks held: %d"), Inventory->GetSlotCount()));
	const float Capacity = Inventory->GetWeightCapacity();
	AddLine(Capacity > 0.0f
		? FString::Printf(TEXT("Weight: %.1f / %.1f"), Inventory->GetUsedWeight(), Capacity)
		: FString::Printf(TEXT("Weight: %.1f (no limit)"), Inventory->GetUsedWeight()));

	AddHeader(TEXT("EQUIPPED CASE"));
	UNexusItemDefinition* CaseDef = Inventory->GetEquippedCaseDefinition();
	AddLine(CaseDef ? NexusEditorUtil::DisplayLabel(CaseDef, CaseDef->DisplayName) : FString(TEXT("(none)")));

	AddHeader(TEXT("CHARM SOCKETS"));
	const FGameplayTagContainer Slots = Inventory->GetCaseCharmSlots();
	if (Slots.IsEmpty())
	{
		AddLine(TEXT("(no charm slots)"), FSlateColor::UseSubduedForeground());
	}
	else
	{
		for (const FGameplayTag& Slot : Slots)
		{
			UNexusItemDefinition* Charm = Inventory->GetSocketedCharm(Slot);
			AddLine(FString::Printf(TEXT("%s: %s"), *NexusEditorUtil::TagLeaf(Slot),
				Charm ? *NexusEditorUtil::DisplayLabel(Charm, Charm->DisplayName) : TEXT("(empty)")));
		}
	}

	AddHeader(TEXT("OFF-GRID ITEMS"));
	int32 OffGrid = 0;
	for (UNexusItemInstance* Instance : Inventory->GetItems())
	{
		if (!Instance || Instance->GetGridPosition() != FIntPoint(-1, -1))
		{
			continue;
		}
		++OffGrid;
		UNexusItemDefinition* Def = Instance->GetDefinition();
		AddLine(FString::Printf(TEXT("%s x%d"),
			Def ? *NexusEditorUtil::DisplayLabel(Def, Def->DisplayName) : TEXT("?"), Instance->GetStackCount()));
	}
	if (OffGrid == 0)
	{
		AddLine(TEXT("(none)"), FSlateColor::UseSubduedForeground());
	}
}

void SNexusLiveInventory::RefreshItemBox()
{
	if (!BoxList.IsValid())
	{
		return;
	}
	BoxList->ClearChildren();

	const FSlateFontInfo BoldFont = FCoreStyle::GetDefaultFontStyle("Bold", 9);
	auto AddHeader = [this, BoldFont](const FString& Text)
	{
		BoxList->AddSlot().AutoHeight().Padding(2.0f, 8.0f, 2.0f, 2.0f)
		[ SNew(STextBlock).Text(FText::FromString(Text)).Font(BoldFont) ];
	};
	auto AddLine = [this](const FString& Text, FSlateColor Color = FSlateColor::UseForeground())
	{
		BoxList->AddSlot().AutoHeight().Padding(2.0f, 1.0f)
		[ SNew(STextBlock).Text(FText::FromString(Text)).ColorAndOpacity(Color).AutoWrapText(true) ];
	};

	UNexusItemContainerSubsystem* Box = GetBoxSubsystem();
	if (!Box)
	{
		AddLine(TEXT("Start Play-In-Editor to inspect the shared item box."), FSlateColor::UseSubduedForeground());
		return;
	}

	AddHeader(TEXT("WALLET"));
	AddLine(FString::Printf(TEXT("Currency: %d"), Box->GetCurrency()));

	AddHeader(TEXT("ITEM BOX"));
	UNexusItemContainer* Container = Box->GetBox();
	int32 Count = 0;
	if (Container)
	{
		for (UNexusItemInstance* Instance : Container->GetItems())
		{
			if (!Instance) { continue; }
			++Count;
			UNexusItemDefinition* Def = Instance->GetDefinition();
			AddLine(FString::Printf(TEXT("%s x%d"),
				Def ? *NexusEditorUtil::DisplayLabel(Def, Def->DisplayName) : TEXT("?"), Instance->GetStackCount()));
		}
	}
	if (Count == 0)
	{
		AddLine(TEXT("(box is empty)"), FSlateColor::UseSubduedForeground());
	}
}

// --- Pickers ------------------------------------------------------------------------------

void SNexusLiveInventory::RebuildPickLists()
{
	SpawnOptions.Reset();
	CaseOptions.Reset();

	TArray<UNexusItemDefinition*> Items;
	NexusEditorUtil::GatherAssets(Items);
	Items.Sort([](const UNexusItemDefinition& A, const UNexusItemDefinition& B) { return A.GetName() < B.GetName(); });

	for (UNexusItemDefinition* Item : Items)
	{
		if (!Item) { continue; }
		TSharedPtr<FPick> Pick = MakeShared<FPick>();
		Pick->Def = Item;
		Pick->Label = NexusEditorUtil::DisplayLabel(Item, Item->DisplayName);
		SpawnOptions.Add(Pick);

		if (NexusEditorUtil::HasCaseFragment(Item))
		{
			TSharedPtr<FPick> CasePick = MakeShared<FPick>();
			CasePick->Def = Item;
			CasePick->Label = Pick->Label;
			CaseOptions.Add(CasePick);
		}
	}

	// Keep a valid selection so the combos always show something sensible.
	if ((!SelectedSpawn.IsValid() || !SpawnOptions.Contains(SelectedSpawn)) && SpawnOptions.Num() > 0)
	{
		SelectedSpawn = SpawnOptions[0];
	}
	if ((!SelectedCase.IsValid() || !CaseOptions.Contains(SelectedCase)) && CaseOptions.Num() > 0)
	{
		SelectedCase = CaseOptions[0];
	}

	if (SpawnCombo.IsValid()) { SpawnCombo->RefreshOptions(); }
	if (CaseCombo.IsValid()) { CaseCombo->RefreshOptions(); }
}

// --- Mutations (gated on a live PIE world) ------------------------------------------------

FReply SNexusLiveInventory::OnSpawnClicked()
{
	APawn* Pawn = GetPlayerPawn();
	UNexusItemDefinition* Def = SelectedSpawn.IsValid() ? SelectedSpawn->Def.Get() : nullptr;
	if (Pawn && Def)
	{
		FNexusAcquireParams Params;
		Params.bAutoEquipIfPossible = false; // keep it in inventory so it shows on the grid
		Params.bSkipCeremony = true;         // debug give — no cinematic intro
		const int32 Count = FMath::Max(1, SpawnCount);
		const FNexusAcquireResult Result = UNexusInventoryAcquireLibrary::AcquireItem(Pawn, Def, Count, Params);
		LastActionResult = FText::FromString(FString::Printf(
			TEXT("Spawned %d x %s — added %d, remainder %d."), Count, *Def->GetName(), Result.AmountAdded, Result.Remainder));
		bForceRefresh = true;
		RefreshLive();
	}
	return FReply::Handled();
}

FReply SNexusLiveInventory::OnSwapCaseClicked()
{
	UNexusInventoryComponent* Inventory = GetPlayerInventory();
	UNexusItemContainerSubsystem* Box = GetBoxSubsystem();
	UNexusItemDefinition* CaseDef = SelectedCase.IsValid() ? SelectedCase->Def.Get() : nullptr;
	if (Inventory && Box && CaseDef)
	{
		Box->SwapCase(Inventory, CaseDef);
		LastActionResult = FText::FromString(FString::Printf(
			TEXT("Swapped case to %s — any overflow was sent to the item box."), *CaseDef->GetName()));
		bForceRefresh = true;
		RefreshLive();
	}
	return FReply::Handled();
}

FReply SNexusLiveInventory::OnAutoArrangeClicked()
{
	if (UNexusInventoryComponent* Inventory = GetPlayerInventory())
	{
		Inventory->OptimizeSpatialSection();
		LastActionResult = LOCTEXT("AutoArranged", "Repacked the spatial grid.");
		bForceRefresh = true;
		RefreshLive();
	}
	return FReply::Handled();
}

FReply SNexusLiveInventory::OnClearClicked()
{
	if (UNexusInventoryComponent* Inventory = GetPlayerInventory())
	{
		Inventory->ClearAll();
		LastActionResult = LOCTEXT("Cleared", "Cleared the player inventory.");
		bForceRefresh = true;
		RefreshLive();
	}
	return FReply::Handled();
}

FText SNexusLiveInventory::GetStatusText() const
{
	if (!IsLive())
	{
		return LOCTEXT("NotLive", "Start Play-In-Editor to inspect the live inventory (read-only until then).");
	}
	return LOCTEXT("Live", "● Live — reflecting the player's real runtime container.");
}

#undef LOCTEXT_NAMESPACE
