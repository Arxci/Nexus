// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusPlayerCameraManager.h"

#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "NexusCameraModifier_AimFOV.h"

ANexusPlayerCameraManager::ANexusPlayerCameraManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ViewPitchMin = -80.0f;
	ViewPitchMax = 80.0f;
	DefaultFOV   = 70.0f;

	AimFOVModifierClass = UNexusCameraModifier_AimFOV::StaticClass();
}

void ANexusPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	// Eager-create so the modifier list ordering is stable from the first frame.
	GetOrCreateAimFOVModifier();
}

void ANexusPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	TickRecoil(DeltaTime);
	Super::UpdateCamera(DeltaTime);
}

void ANexusPlayerCameraManager::StartCameraFadeWithDelay(const float FromAlpha, const float ToAlpha, const float InFadeTime, const float InDelayTime, const FLinearColor InFadeColor, const bool bInFadeAudio, const bool bInHoldWhenFinished)
{
	GetWorldTimerManager().SetTimer(CameraFadeDelayHandle, FTimerDelegate::CreateLambda([this, FromAlpha, ToAlpha, InFadeTime, InFadeColor, bInFadeAudio, bInHoldWhenFinished]()
	{
		StartCameraFade(FromAlpha, ToAlpha, InFadeTime, InFadeColor, bInFadeAudio, bInHoldWhenFinished);
	}), InDelayTime, false);
}

void ANexusPlayerCameraManager::KickCamera(FVector2D PitchYawDegrees)
{
	APlayerController* PC = GetOwningPlayerController();
	if (!PC) return;

	FRotator CR = PC->GetControlRotation();
	CR.Pitch -= PitchYawDegrees.X;
	CR.Yaw   += PitchYawDegrees.Y;
	PC->SetControlRotation(CR);

	AccumulatedRecoilPitch = FMath::Min(AccumulatedRecoilPitch + PitchYawDegrees.X, RecoilPitchAccumCap);
	AccumulatedRecoilYaw   += PitchYawDegrees.Y;
}

void ANexusPlayerCameraManager::BlendToFOV(float TargetFOV, float Duration)
{
	UNexusCameraModifier_AimFOV* Mod = GetOrCreateAimFOVModifier();
	if (!Mod) return;

	// The modifier expresses its effect as a delta from DefaultFOV so it can
	// stack with other FOV-altering modifiers (crouch, run, ...).
	const float Delta = TargetFOV - DefaultFOV;
	Mod->StartBlend(Delta, Duration);
}

void ANexusPlayerCameraManager::EndAimFOVBlend(float Duration)
{
	if (UNexusCameraModifier_AimFOV* Mod = GetOrCreateAimFOVModifier())
	{
		Mod->EndBlend(Duration);
	}
}

UNexusCameraModifier_AimFOV* ANexusPlayerCameraManager::GetOrCreateAimFOVModifier()
{
	if (AimFOVModifier) return AimFOVModifier;

	UClass* Class = AimFOVModifierClass ? AimFOVModifierClass.Get() : UNexusCameraModifier_AimFOV::StaticClass();
	UCameraModifier* Created = AddNewCameraModifier(Class);
	AimFOVModifier = Cast<UNexusCameraModifier_AimFOV>(Created);
	return AimFOVModifier;
}

void ANexusPlayerCameraManager::TickRecoil(float DeltaTime)
{
	if (FMath::IsNearlyZero(AccumulatedRecoilPitch) && FMath::IsNearlyZero(AccumulatedRecoilYaw)) return;

	APlayerController* PC = GetOwningPlayerController();
	if (!PC) return;

	const float Recovery = RecoilRecoveryRate * DeltaTime;
	FRotator CR          = PC->GetControlRotation();

	const float PitchRecover = FMath::Min(Recovery, FMath::Abs(AccumulatedRecoilPitch));
	if (PitchRecover > 0.0f)
	{
		const float Sign = FMath::Sign(AccumulatedRecoilPitch);
		CR.Pitch += Sign * PitchRecover;
		AccumulatedRecoilPitch -= Sign * PitchRecover;
	}

	const float YawRecover = FMath::Min(Recovery, FMath::Abs(AccumulatedRecoilYaw));
	if (YawRecover > 0.0f)
	{
		const float Sign = FMath::Sign(AccumulatedRecoilYaw);
		CR.Yaw -= Sign * YawRecover;
		AccumulatedRecoilYaw -= Sign * YawRecover;
	}

	PC->SetControlRotation(CR);
}