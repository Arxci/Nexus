// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "NexusPlayerCameraManager.generated.h"

class USkeletalMeshComponent;

UCLASS()
class NEXUS_API ANexusPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	ANexusPlayerCameraManager(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	void StartCameraFadeWithDelay(const float FromAlpha, const float ToAlpha, const float InFadeTime, const float InDelayTime, const FLinearColor InFadeColor, const bool bInFadeAudio, const bool bInHoldWhenFinished);

public:
	/** Master toggle for the head-bone-driven view animation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nexus|View Animation")
	bool bEnableViewBoneAnimation = true;

	/** Bone whose animated motion drives the view. Defaults to the UE5 skeleton head. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nexus|View Animation")
	FName ViewBoneName = FName("head");

	/** Scales the positional offset (head bob). 0 disables translation; expose as a player setting. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nexus|View Animation", meta = (ClampMin = "0.0"))
	float ViewBoneLocationScale = 1.0f;

	/** Scales the rotational offset (view kick/lean). 0 disables rotation; expose as a player setting. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nexus|View Animation", meta = (ClampMin = "0.0"))
	float ViewBoneRotationScale = 1.0f;

protected:


private:
	FTimerHandle CameraFadeDelayHandle;

	TWeakObjectPtr<USkeletalMeshComponent> CachedMesh;
	FName CachedBoneName = NAME_None;
	int32 CachedBoneIndex = INDEX_NONE;
	FTransform CachedRefBoneComponentSpace = FTransform::Identity;
};