#include "NexusPlayerCameraManager.h"

#include "GameFramework/PlayerController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"

#include "Nexus/Character/NexusCharacterBase.h"

namespace
{
	// Accumulate a bone's reference-pose (bind pose) transform into component space by
	// walking up the parent chain — the neutral the animated bone is measured against.
	FTransform ComputeRefPoseComponentSpace(const USkeletalMeshComponent* Mesh, const int32 BoneIndex)
	{
		const USkeletalMesh* Asset = Mesh ? Mesh->GetSkeletalMeshAsset() : nullptr;
		if (!Asset || BoneIndex == INDEX_NONE)
		{
			return FTransform::Identity;
		}

		const FReferenceSkeleton& RefSkeleton = Asset->GetRefSkeleton();
		const TArray<FTransform>& LocalPose = RefSkeleton.GetRefBonePose();
		if (!LocalPose.IsValidIndex(BoneIndex))
		{
			return FTransform::Identity;
		}

		FTransform Accumulated = LocalPose[BoneIndex];
		for (int32 Parent = RefSkeleton.GetParentIndex(BoneIndex); Parent != INDEX_NONE; Parent = RefSkeleton.GetParentIndex(Parent))
		{
			Accumulated = LocalPose[Parent] * Accumulated;
		}
		return Accumulated;
	}
}

ANexusPlayerCameraManager::ANexusPlayerCameraManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ViewPitchMin = -80.0f;
	ViewPitchMax = 80.0f;
	DefaultFOV   = 70.0f;
}

void ANexusPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();
}



void ANexusPlayerCameraManager::StartCameraFadeWithDelay(const float FromAlpha, const float ToAlpha, const float InFadeTime, const float InDelayTime, const FLinearColor InFadeColor, const bool bInFadeAudio, const bool bInHoldWhenFinished)
{
	GetWorldTimerManager().SetTimer(CameraFadeDelayHandle, FTimerDelegate::CreateLambda([this, FromAlpha, ToAlpha, InFadeTime, InFadeColor, bInFadeAudio, bInHoldWhenFinished]()
	{
		StartCameraFade(FromAlpha, ToAlpha, InFadeTime, InFadeColor, bInFadeAudio, bInHoldWhenFinished);
	}), InDelayTime, false);
}