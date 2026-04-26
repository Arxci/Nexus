// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "NexusCameraModifier_AimFOV.h"
#include "NexusPlayerCameraManager.generated.h"

UCLASS()
class NEXUS_API ANexusPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	ANexusPlayerCameraManager(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void UpdateCamera(float DeltaTime) override;

	void StartCameraFadeWithDelay(const float FromAlpha, const float ToAlpha, const float InFadeTime, const float InDelayTime, const FLinearColor InFadeColor, const bool bInFadeAudio, const bool bInHoldWhenFinished);

	/**
	 * Push a one-shot recoil impulse onto the controller's view rotation.
	 *  - X = pitch up in degrees (typically positive for kick up)
	 *  - Y = yaw deflection in degrees (random sign, usually small)
	 * Direct rotation change — affects aim, not just visuals — and recovers
	 * toward zero at RecoilRecoveryRate degrees/second. Doesn't fight your
	 * camera modifiers because they compose on top of ControlRotation, they
	 * don't author it.
	 */
	UFUNCTION(BlueprintCallable, Category = "Camera|Recoil")
	void KickCamera(FVector2D PitchYawDegrees);

	/**
	 * Blend the aim FOV by adjusting the AimFOV modifier's delta. Uses a
	 * UNexusCameraModifier_AimFOV under the hood so it composes additively
	 * with your other modifiers (crouch FOV bumps, run FOV pumps, etc.).
	 *
	 * @param TargetFOV  Desired final FOV. Subtract from DefaultFOV to derive a delta.
	 * @param Duration   Blend time in seconds. 0 snaps.
	 */
	UFUNCTION(BlueprintCallable, Category = "Camera|FOV")
	void BlendToFOV(float TargetFOV, float Duration);

	/**
	 * Blend the aim FOV delta back to zero. Use when ending aim — avoids the
	 * "what was DefaultFOV at apply-time?" bookkeeping that BlendToFOV requires.
	 */
	UFUNCTION(BlueprintCallable, Category = "Camera|FOV")
	void EndAimFOVBlend(float Duration);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Recoil", meta = (ClampMin = "0.0"))
	float RecoilRecoveryRate = 60.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|Recoil", meta = (ClampMin = "0.0"))
	float RecoilPitchAccumCap = 12.0f;

	/** Class spawned for the aim-FOV modifier. Override to customise blend behaviour. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera|FOV")
	TSubclassOf<UNexusCameraModifier_AimFOV> AimFOVModifierClass;

private:
	FTimerHandle CameraFadeDelayHandle;

	// Recoil
	float AccumulatedRecoilPitch = 0.0f;
	float AccumulatedRecoilYaw   = 0.0f;
	void TickRecoil(float DeltaTime);

	UPROPERTY(Transient)
	TObjectPtr<UNexusCameraModifier_AimFOV> AimFOVModifier;

	UNexusCameraModifier_AimFOV* GetOrCreateAimFOVModifier();
};

