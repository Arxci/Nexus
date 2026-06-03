#include "Preview/SNexusItemViewport.h"

#include "AdvancedPreviewScene.h"
#include "EditorViewportClient.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"
#include "StructUtils/InstancedStruct.h"

#include "UObject/Package.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemFragment.h"
#include "Nexus/Inventory/Fragments/Equippable/NexusFragment_Equippable.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"

namespace
{
	const FNexusFragment_Equippable* FindEquippable(const UNexusItemDefinition* Item)
	{
		if (!Item) { return nullptr; }
		for (const TInstancedStruct<FNexusItemFragment>& Frag : Item->Fragments)
		{
			if (!Frag.IsValid()) { continue; }
			const UScriptStruct* Type = Frag.GetScriptStruct();
			if (Type && Type->IsChildOf(FNexusFragment_Equippable::StaticStruct()))
			{
				return Frag.GetPtr<const FNexusFragment_Equippable>();
			}
		}
		return nullptr;
	}

	/**
	 * Spawn a mesh component for each slot's authored DefaultAttachment, attach
	 * it to ParentMesh at the slot's socket, and recurse into the attachment's
	 * own ProvidedSlots. Mirrors the shape of the runtime
	 * UNexusAssemblyComponent::RebuildFromInstance walk, without persistence or
	 * stat resolution — the editor preview just needs the visuals.
	 *
	 * Every spawned attachment def is added to OutTracked so the viewport's
	 * global property-change hook can cheaply test "is the edited object one
	 * of mine?" via a set lookup.
	 */
	void SpawnSlotsRecursive(
		FAdvancedPreviewScene* Scene,
		UMeshComponent* ParentMesh,
		const TArray<FAssemblySlotDefinition>& Slots,
		TArray<TObjectPtr<UMeshComponent>>& OutComponents,
		TSet<TWeakObjectPtr<UNexusAttachmentDefinition>>& OutTracked)
	{
		if (!Scene || !ParentMesh)
		{
			return;
		}

		for (const FAssemblySlotDefinition& Slot : Slots)
		{
			UNexusAttachmentDefinition* AttachDef = Slot.DefaultAttachment.LoadSynchronous();
			if (!AttachDef)
			{
				continue;
			}

			USkeletalMesh* Skeletal = AttachDef->SkeletalMesh.LoadSynchronous();
			UStaticMesh* Static = (!Skeletal) ? AttachDef->StaticMesh.LoadSynchronous() : nullptr;
			if (!Skeletal && !Static)
			{
				continue;
			}

			UMeshComponent* NewMesh = nullptr;
			if (Skeletal)
			{
				USkeletalMeshComponent* SkelComp = NewObject<USkeletalMeshComponent>(
					GetTransientPackage(), NAME_None, RF_Transient);
				SkelComp->SetSkeletalMesh(Skeletal);
				NewMesh = SkelComp;
			}
			else
			{
				UStaticMeshComponent* StaticComp = NewObject<UStaticMeshComponent>(
					GetTransientPackage(), NAME_None, RF_Transient);
				StaticComp->SetStaticMesh(Static);
				NewMesh = StaticComp;
			}

			Scene->AddComponent(NewMesh, FTransform::Identity);
			NewMesh->AttachToComponent(
				ParentMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Slot.AttachSocket);
			OutComponents.Add(NewMesh);
			OutTracked.Add(AttachDef);

			SpawnSlotsRecursive(Scene, NewMesh, AttachDef->ProvidedSlots, OutComponents, OutTracked);
		}
	}
}

void SNexusItemViewport::Construct(const FArguments& InArgs)
{
	PreviewScene = MakeShared<FAdvancedPreviewScene>(FPreviewScene::ConstructionValues());

	// One of each mesh kind, swapped between assets so the preview scene heap
	// doesn't churn on every selection change.
	SkeletalPreviewComponent = NewObject<USkeletalMeshComponent>(GetTransientPackage(), NAME_None, RF_Transient);
	StaticPreviewComponent = NewObject<UStaticMeshComponent>(GetTransientPackage(), NAME_None, RF_Transient);

	PreviewScene->AddComponent(SkeletalPreviewComponent.Get(), FTransform::Identity);
	PreviewScene->AddComponent(StaticPreviewComponent.Get(), FTransform::Identity);

	SkeletalPreviewComponent->SetVisibility(false);
	StaticPreviewComponent->SetVisibility(false);

	SEditorViewport::Construct(SEditorViewport::FArguments());

	// Edits to attachment defs / mesh assets land here even when the details
	// panel is bound to the host gun — the details panel only notifies about
	// its own object.
	FCoreUObjectDelegates::OnObjectPropertyChanged.AddSP(this, &SNexusItemViewport::OnObjectPropertyChanged);
}

SNexusItemViewport::~SNexusItemViewport()
{
	FCoreUObjectDelegates::OnObjectPropertyChanged.RemoveAll(this);

	if (ViewportClient.IsValid())
	{
		ViewportClient->Viewport = nullptr;
	}
}

TSharedRef<FEditorViewportClient> SNexusItemViewport::MakeEditorViewportClient()
{
	ViewportClient = MakeShared<FEditorViewportClient>(
		/*InModeTools=*/ nullptr,
		PreviewScene.Get(),
		StaticCastSharedRef<SEditorViewport>(AsShared()));

	ViewportClient->SetViewportType(LVT_Perspective);
	ViewportClient->SetRealtime(true);
	ViewportClient->bSetListenerPosition = false;
	ViewportClient->EngineShowFlags.SetGrid(true);
	ViewportClient->EngineShowFlags.SetSelection(false);
	ViewportClient->ViewFOV = 50.0f;
	ViewportClient->SetViewLocation(FVector(120.0f, 120.0f, 80.0f));
	ViewportClient->SetViewRotation(FRotator(-15.0f, -135.0f, 0.0f));

	return ViewportClient.ToSharedRef();
}

void SNexusItemViewport::SetPreviewAsset(UObject* Asset)
{
	if (CurrentAsset.Get() == Asset)
	{
		return;
	}
	CurrentAsset = Asset;

	if (UNexusAttachmentDefinition* Attachment = Cast<UNexusAttachmentDefinition>(Asset))
	{
		ApplyAttachment(Attachment);
	}
	else if (UNexusItemDefinition* Item = Cast<UNexusItemDefinition>(Asset))
	{
		ApplyItem(Item);
	}
	else
	{
		ApplyMeshes(nullptr, nullptr);
	}

	// Whether the new asset is an item, an attachment, or neither, the host's
	// attachment children get torn down here; only items rebuild new ones.
	RebuildAttachmentTree();
}

void SNexusItemViewport::ApplyItem(UNexusItemDefinition* Item)
{
	// Prefer the equipped/world mesh (a skeletal weapon mesh) when present; fall
	// back to the static pickup mesh so consumables, ammo and treasure still preview.
	USkeletalMesh* Skeletal = nullptr;
	if (const FNexusFragment_Equippable* Equippable = FindEquippable(Item))
	{
		Skeletal = Equippable->WorldMesh.LoadSynchronous();
	}

	UStaticMesh* Static = Skeletal ? nullptr : (Item ? Item->PickupMesh.LoadSynchronous() : nullptr);
	ApplyMeshes(Skeletal, Static);
}

void SNexusItemViewport::ApplyAttachment(UNexusAttachmentDefinition* Attachment)
{
	USkeletalMesh* Skeletal = Attachment ? Attachment->SkeletalMesh.LoadSynchronous() : nullptr;
	UStaticMesh* Static = (Attachment && !Skeletal) ? Attachment->StaticMesh.LoadSynchronous() : nullptr;
	ApplyMeshes(Skeletal, Static);
}

void SNexusItemViewport::ApplyMeshes(USkeletalMesh* Skeletal, UStaticMesh* Static)
{
	SkeletalPreviewComponent->SetSkeletalMesh(Skeletal);
	SkeletalPreviewComponent->SetVisibility(Skeletal != nullptr);

	StaticPreviewComponent->SetStaticMesh(Static);
	StaticPreviewComponent->SetVisibility(Static != nullptr);

	FocusOnPreview();
}

void SNexusItemViewport::FocusOnPreview()
{
	if (!ViewportClient.IsValid())
	{
		return;
	}

	FBox Bounds(ForceInit);
	if (SkeletalPreviewComponent && SkeletalPreviewComponent->IsVisible() && SkeletalPreviewComponent->GetSkeletalMeshAsset())
	{
		Bounds += SkeletalPreviewComponent->Bounds.GetBox();
	}
	if (StaticPreviewComponent && StaticPreviewComponent->IsVisible() && StaticPreviewComponent->GetStaticMesh())
	{
		Bounds += StaticPreviewComponent->Bounds.GetBox();
	}

	if (Bounds.IsValid)
	{
		ViewportClient->FocusViewportOnBox(Bounds, /*bInstant=*/ true);
	}
	ViewportClient->Invalidate();
}

void SNexusItemViewport::RebuildAttachmentTree()
{
	ClearAttachmentComponents();

	UNexusItemDefinition* Item = Cast<UNexusItemDefinition>(CurrentAsset.Get());
	if (!Item || !PreviewScene.IsValid())
	{
		return;
	}

	const FNexusFragment_Equippable* Equippable = FindEquippable(Item);
	if (!Equippable || Equippable->Slots.Num() == 0)
	{
		return;
	}

	// Pick the host: prefer the visible skeletal (weapon WorldMesh), fall back to
	// the visible static (pickup mesh on a non-weapon equippable). Sockets only
	// resolve against whichever one's actually showing.
	UMeshComponent* HostMesh = nullptr;
	if (SkeletalPreviewComponent && SkeletalPreviewComponent->IsVisible() &&
		SkeletalPreviewComponent->GetSkeletalMeshAsset())
	{
		HostMesh = SkeletalPreviewComponent.Get();
	}
	else if (StaticPreviewComponent && StaticPreviewComponent->IsVisible() &&
		StaticPreviewComponent->GetStaticMesh())
	{
		HostMesh = StaticPreviewComponent.Get();
	}
	if (!HostMesh)
	{
		return;
	}

	SpawnSlotsRecursive(PreviewScene.Get(), HostMesh, Equippable->Slots,
		AttachmentMeshComponents, TrackedAttachments);
}

void SNexusItemViewport::ClearAttachmentComponents()
{
	for (TObjectPtr<UMeshComponent>& Comp : AttachmentMeshComponents)
	{
		if (UMeshComponent* C = Comp.Get())
		{
			if (PreviewScene.IsValid())
			{
				PreviewScene->RemoveComponent(C);
			}
			C->DestroyComponent();
		}
	}
	AttachmentMeshComponents.Empty();
	TrackedAttachments.Empty();
}

void SNexusItemViewport::RefreshPreview()
{
	// SetPreviewAsset short-circuits when the asset hasn't changed; clear the
	// cache first so a forced refresh re-walks the slot tree and re-loads meshes.
	UObject* Asset = CurrentAsset.Get();
	CurrentAsset = nullptr;
	SetPreviewAsset(Asset);
}

void SNexusItemViewport::OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& /*Event*/)
{
	if (ShouldRefreshFor(Object))
	{
		RefreshPreview();
	}
}

bool SNexusItemViewport::ShouldRefreshFor(UObject* Object) const
{
	if (!Object || !CurrentAsset.IsValid())
	{
		return false;
	}

	// 1. The asset being shown itself.
	if (Object == CurrentAsset.Get())
	{
		return true;
	}

	// 2. An attachment def whose mesh is currently rendered in the tree.
	if (UNexusAttachmentDefinition* Attachment = Cast<UNexusAttachmentDefinition>(Object))
	{
		if (TrackedAttachments.Contains(Attachment))
		{
			return true;
		}
	}

	// 3. A mesh asset currently bound to one of our components — covers reimport
	// and "user edited the mesh asset directly" cases.
	if (USkeletalMesh* SkelMesh = Cast<USkeletalMesh>(Object))
	{
		if (SkeletalPreviewComponent && SkeletalPreviewComponent->GetSkeletalMeshAsset() == SkelMesh)
		{
			return true;
		}
		for (const TObjectPtr<UMeshComponent>& Comp : AttachmentMeshComponents)
		{
			if (const USkeletalMeshComponent* SkMC = Cast<USkeletalMeshComponent>(Comp.Get()))
			{
				if (SkMC->GetSkeletalMeshAsset() == SkelMesh) { return true; }
			}
		}
	}
	if (UStaticMesh* StaticMeshAsset = Cast<UStaticMesh>(Object))
	{
		if (StaticPreviewComponent && StaticPreviewComponent->GetStaticMesh() == StaticMeshAsset)
		{
			return true;
		}
		for (const TObjectPtr<UMeshComponent>& Comp : AttachmentMeshComponents)
		{
			if (const UStaticMeshComponent* StMC = Cast<UStaticMeshComponent>(Comp.Get()))
			{
				if (StMC->GetStaticMesh() == StaticMeshAsset) { return true; }
			}
		}
	}

	return false;
}
