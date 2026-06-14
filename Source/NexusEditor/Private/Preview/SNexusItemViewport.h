#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"

class FAdvancedPreviewScene;
class FEditorViewportClient;
class UMeshComponent;
class UNexusAttachmentDefinition;
class UNexusItemDefinition;
class USkeletalMesh;
class USkeletalMeshComponent;
class UStaticMesh;
class UStaticMeshComponent;

/**
 * Embedded 3D preview for an item or attachment in the Nexus Creator window.
 *
 * Drives an FAdvancedPreviewScene with the asset's authored mesh — UStaticMesh
 * from UNexusItemDefinition::PickupMesh (or the weapon-equippable WorldMesh, if
 * present) for items, and SkeletalMesh / StaticMesh from UNexusAttachmentDefinition
 * for attachments. Soft-references are loaded synchronously on demand; the
 * camera re-focuses on the new mesh's bounds whenever the asset changes.
 *
 * Keeps a single USkeletalMeshComponent + UStaticMeshComponent in the scene and
 * swaps their content (rather than spawning new components per asset), so the
 * preview can churn through many selections without the scene heap thrashing.
 */
class SNexusItemViewport : public SEditorViewport
{
public:
	SLATE_BEGIN_ARGS(SNexusItemViewport) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual ~SNexusItemViewport() override;

	/** Show this asset (a UNexusItemDefinition or UNexusAttachmentDefinition). Null clears the preview. */
	void SetPreviewAsset(UObject* Asset);

	/** Force a full re-resolve of the current asset (bypasses the same-asset short-circuit). */
	void RefreshPreview();

protected:
	// SEditorViewport
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

private:
	void ApplyItem(UNexusItemDefinition* Item);
	void ApplyAttachment(UNexusAttachmentDefinition* Attachment);
	void ApplyMeshes(USkeletalMesh* Skeletal, UStaticMesh* Static);
	void FocusOnPreview();

	/**
	 * Walk the host item's equippable Slots and spawn a mesh component per
	 * authored DefaultAttachment, attached at the slot's socket. Recurses into
	 * each attachment's own ProvidedSlots so a nested loadout (rail with
	 * magnifier, magazine with extender, ...) reads correctly. Always clears
	 * the previous attachment tree first.
	 */
	void RebuildAttachmentTree();
	void ClearAttachmentComponents();

	/**
	 * Global PostEditChange hook. Fires whenever ANY UObject's property changes
	 * in the editor, so we can pick up edits to attachment assets the gun is
	 * referencing (the details panel only notifies about its bound object).
	 * The filter keeps cost trivial: a pointer-equality test against the
	 * current asset, the tracked attachment set, and the mesh assets each
	 * spawned component currently holds.
	 */
	void OnObjectPropertyChanged(UObject* Object, struct FPropertyChangedEvent& Event);
	bool ShouldRefreshFor(UObject* Object) const;

	TSharedPtr<FAdvancedPreviewScene> PreviewScene;
	TSharedPtr<FEditorViewportClient> ViewportClient;

	TObjectPtr<USkeletalMeshComponent> SkeletalPreviewComponent;
	TObjectPtr<UStaticMeshComponent> StaticPreviewComponent;

	/** Dynamic per-attachment mesh components, torn down + rebuilt per asset change. */
	TArray<TObjectPtr<UMeshComponent>> AttachmentMeshComponents;

	/** Attachment defs currently part of the rendered tree — drives the auto-refresh filter. */
	TSet<TWeakObjectPtr<UNexusAttachmentDefinition>> TrackedAttachments;

	TWeakObjectPtr<UObject> CurrentAsset;
};
