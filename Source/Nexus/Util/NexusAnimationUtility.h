#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NexusAnimationUtility.generated.h"

class UAnimInstance;
class UAnimMontage;

UCLASS()
class NEXUS_API UNexusAnimationUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Plays Montage on Owner's animation mesh (ANexusCharacterBase::GetAnimInstance()).
	// Returns the AnimInstance it played on, or null if Owner isn't a Nexus character, has
	// no anim instance, or the montage didn't start. OutDuration = montage length, 0 on fail.
	UFUNCTION(BlueprintCallable, Category = "Nexus|Animation")
	static UAnimInstance* PlayMontageOnOwner(const AActor* Owner, UAnimMontage* Montage, float& OutDuration);
};