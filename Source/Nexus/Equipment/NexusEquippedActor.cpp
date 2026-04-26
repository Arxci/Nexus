// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusEquippedActor.h"

#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Inventory/Fragments/NexusFragment_Equippable.h"

ANexusEquippedActor::ANexusEquippedActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetCastShadow(true);
}

void ANexusEquippedActor::InitializeFromInstance(UNexusItemInstance* Instance)
{
	SourceInstance = Instance;
	if (!Instance) return;

	const UNexusItemDefinition* Def = Instance->GetDefinition();
	if (!Def) return;

	if (const FNexusFragment_Equippable* Eq = Def->FindFragment<FNexusFragment_Equippable>())
	{
		if (USkeletalMesh* Loaded = Eq->WorldMesh.LoadSynchronous())
		{
			Mesh->SetSkeletalMesh(Loaded);
		}
	}

	K2_OnInitializedFromInstance();
}

FTransform ANexusEquippedActor::GetSocketTransform(FName SocketName) const
{
	if (Mesh && Mesh->DoesSocketExist(SocketName))
	{
		return Mesh->GetSocketTransform(SocketName);
	}
	return GetActorTransform();
}