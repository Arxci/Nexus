#include "NexusHeroPlayerUtility.h"

#include "GameFramework/Pawn.h"

#include "GameFramework/PlayerController.h"


bool UNexusHeroPlayerUtility::CameraForwardTrace(
	const APawn* Pawn,
	const float Distance,
	const ETraceTypeQuery TraceChannel,
	FHitResult& OutHit,
	const TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType, const float DrawTime)
{
	if (!Pawn) return false;

	const APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
	if (!PC) return false;

	FVector CamLoc;
	FRotator CamRot;
	PC->GetPlayerViewPoint(CamLoc, CamRot);

	const FVector Start = CamLoc;
	const FVector End   = Start + CamRot.Vector() * Distance;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(const_cast<APawn*>(Pawn));

	return UKismetSystemLibrary::LineTraceSingle(
		Pawn,                                              // WorldContextObject
		Start,
		End,
		TraceChannel,
		false,                                             // bTraceComplex
		ActorsToIgnore,
		DrawDebugType,
		OutHit,
		true,                                              // bIgnoreSelf
		FLinearColor::Red,
		FLinearColor::Green,
		DrawTime                                             // DrawTime
	);
}
