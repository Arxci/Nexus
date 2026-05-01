// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "NexusItemFragment.generated.h"

class UNexusItemDefinition;
class UNexusItemInstance;


USTRUCT(BlueprintType, meta = (Hidden))
struct NEXUS_API FNexusItemFragment
{
	GENERATED_BODY()

	virtual ~FNexusItemFragment() = default;
	
	virtual void InitializeInstance(UNexusItemInstance* Instance) const {}
};