#include "NexusAbility_WeaponMelee.h"

#include "Animation/AnimMontage.h"

#include "Engine/EngineTypes.h"
#include "Engine/World.h"

#include "GameFramework/Pawn.h"

#include "Kismet/GameplayStatics.h"

#include "Sound/SoundBase.h"

#include "TimerManager.h"

#include "Nexus/Nexus.h"
#include "Nexus/Combat/NexusStaminaComponent.h"
#include "Nexus/Equipment/NexusEquipmentInterface.h"
#include "Nexus/Equipment/NexusEquippedActor.h"
#include "Nexus/Inventory/NexusInventoryComponent.h"
#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Inventory/NexusItemInstance.h"
#include "Nexus/Weapon/Fragments/NexusFragment_Weapon.h"
#include "Nexus/NexusCollisionChannels.h"
#include "Nexus/NexusGameplayTags.h"
#include "Nexus/Weapon/HitDelivery/NexusHitDelivery_MeleeSweep.h"

namespace
{
	// Fallback swing length when a weapon authors no swing montage — the window then spans
	// the whole default duration so the swing still connects.
	constexpr float NexusMeleeDefaultSwingSeconds = 0.5f;
}

UNexusAbility_WeaponMelee::UNexusAbility_WeaponMelee()
{
	AbilityTags.AddTag(NexusGameplayTags::Ability_Weapon_Melee);
	ActivationOwnedTags.AddTag(NexusGameplayTags::Character_State_Weapon_Meleeing);
	// Self-exclusive (one swing at a time) and blocked mid weapon-swap.
	ActivationBlockedTags.AddTag(NexusGameplayTags::Character_State_Weapon_Meleeing);
	ActivationBlockedTags.AddTag(NexusGameplayTags::Character_State_Weapon_Swapping);
	bCooldownOnActivation   = true;
	bCooldownOnDeactivation = false;
}

bool UNexusAbility_WeaponMelee::CanActivateAbility_Implementation() const
{
	if (!Super::CanActivateAbility_Implementation()) return false;

	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon || !Weapon->bHasMelee) return false;

	// Enough stamina for the pending swing weight (no stamina component = unlimited).
	if (const UNexusStaminaComponent* Stamina = GetStamina())
	{
		if (!Stamina->HasStamina(GetSwingStaminaCost(bHeavyNext))) return false;
	}
	return true;
}

bool UNexusAbility_WeaponMelee::RequestActivateAbility()
{
	if (IsOnCooldown()) return false;
	if (!Super::RequestActivateAbility()) return false;
	CommitAbility();
	return true;
}

bool UNexusAbility_WeaponMelee::RequestDeactivateAbility(bool bForce)
{
	if (!bForce && !IsActive()) return false;
	CommitAbilityEnd();
	return true;
}

void UNexusAbility_WeaponMelee::CommitAbility()
{
	Super::CommitAbility(); // Active + Meleeing owned tag + cooldown

	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon || !Weapon->bHasMelee) { CommitAbilityEnd(); return; }

	bSwingHeavy = bHeavyNext && Weapon->Melee.bSupportsHeavy;
	bHeavyNext  = false; // consume the intent

	// Spend stamina for this swing; bail cleanly if it somehow can't be paid.
	if (UNexusStaminaComponent* Stamina = GetStamina())
	{
		if (!Stamina->ConsumeStamina(GetSwingStaminaCost(bSwingHeavy)))
		{
			CommitAbilityEnd();
			return;
		}
	}

	bWindowOpen = false;
	SwingResult = FNexusHitDeliveryResult{};

	// A ranged weapon bashes (Bash); a melee weapon swings (MeleeLight / MeleeHeavy). The
	// montage resolves through the assembly override-then-fallback walk, like Fire / Reload.
	FGameplayTag ActionTag;
	if (Weapon->bHasRanged)
	{
		ActionTag = NexusGameplayTags::Action_Equipment_Weapon_Bash;
	}
	else
	{
		ActionTag = bSwingHeavy
			? NexusGameplayTags::Action_Equipment_Weapon_MeleeHeavy
			: NexusGameplayTags::Action_Equipment_Weapon_MeleeLight;
	}

	float Duration = 0.0f;
	if (const ANexusEquippedActor* Equipped = GetEquippedActor())
	{
		if (UAnimMontage* Montage = Equipped->GetEffectiveHostMontage(ActionTag))
		{
			if (INexusEquipmentInterface* Host = GetEquipmentHost())
			{
				Duration = Host->PlayMontage(Montage);
			}
		}
	}

	if (USoundBase* Swing = NexusWeapon::GetEquippedAsset(Weapon->Melee.SwingSound,
		TEXT("SwingSound"), GetActiveDefinition()))
	{
		if (const AActor* Owner = GetOwner())
		{
			UGameplayStatics::PlaySoundAtLocation(this, Swing, Owner->GetActorLocation());
		}
	}

	// End the ability when the swing finishes. The hit window is opened / closed by the
	// montage's Melee Hit Window notify-state during that span; with no montage authored,
	// open the window for the whole default duration so the swing still connects.
	const float SwingSeconds = Duration > 0.0f ? Duration : NexusMeleeDefaultSwingSeconds;
	if (Duration <= 0.0f)
	{
		OpenHitWindow();
	}

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(TimerHandle_SwingEnd, this,
			&UNexusAbility_WeaponMelee::FinishSwing, SwingSeconds, false);
	}
	else
	{
		FinishSwing();
	}
}

void UNexusAbility_WeaponMelee::CommitAbilityEnd()
{
	if (const UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(TimerHandle_SwingEnd);
	}
	bWindowOpen = false;
	SwingResult = FNexusHitDeliveryResult{};
	Super::CommitAbilityEnd();
}

void UNexusAbility_WeaponMelee::OpenHitWindow()
{
	if (!IsActive()) return;
	bWindowOpen = true;
	SwingResult = FNexusHitDeliveryResult{}; // fresh de-dupe set for this window
}

void UNexusAbility_WeaponMelee::CloseHitWindow()
{
	bWindowOpen = false;
}

bool UNexusAbility_WeaponMelee::CanTick()
{
	return IsActive() && bWindowOpen;
}

void UNexusAbility_WeaponMelee::TickAbility(float DeltaTime)
{
	Super::TickAbility(DeltaTime);
	if (IsActive() && bWindowOpen)
	{
		DoSweep();
	}
}

void UNexusAbility_WeaponMelee::DoSweep()
{
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon || !Weapon->bHasMelee) return;

	ANexusEquippedActor* Equipped = GetEquippedActor();
	const auto Stat = [Equipped](const FGameplayTag& Tag, const float Fallback)
	{
		return Equipped ? Equipped->GetEffectiveStat(Tag, Fallback) : Fallback;
	};

	FVector  Loc;
	FRotator Rot;
	ResolveAimRay(Loc, Rot);

	FNexusHitDeliveryRequest Request;
	Request.Instigator       = GetOwner();
	Request.InstigatorPawn   = Cast<APawn>(GetOwner());
	Request.Causer           = Equipped;
	Request.Origin           = Loc;
	Request.MuzzleLocation   = Loc; // sweep originates at the wielder's viewpoint, forward by reach
	Request.Direction        = Rot.Vector();
	Request.Range            = Stat(NexusGameplayTags::Stat_Melee_Range, Weapon->Melee.Range);
	Request.SweepRadius      = Weapon->Melee.SweepRadius;
	Request.bCleave          = Weapon->Melee.bCleave;
	Request.DamageTypeTag    = Weapon->Melee.DamageTypeTag.IsValid()
		? Weapon->Melee.DamageTypeTag : NexusGameplayTags::Damage_Type_Melee;
	Request.BaseDamage       = Stat(NexusGameplayTags::Stat_Melee_Damage, Weapon->Melee.BaseDamage)
		* (bSwingHeavy ? FMath::Max(1.0f, Weapon->Melee.HeavyDamageMultiplier) : 1.0f);
	Request.ImpulseMagnitude = Stat(NexusGameplayTags::Stat_Melee_Knockback, Weapon->Melee.KnockbackImpulse);
	Request.TraceType        = UEngineTypes::ConvertToTraceType(NexusCollisionChannels::WeaponTrace);
	Request.ExtraContextTags.AddTag(NexusGameplayTags::Damage_Context_Stagger);

	if (const UNexusHitDelivery* Strategy = ResolveMeleeDelivery())
	{
		// SwingResult carries the per-swing de-dupe set across every tick of the window.
		const int32 Before = SwingResult.ReceiversDamaged;
		Strategy->Deliver(Request, SwingResult);

		// Attacker-side hit confirmation for targets newly struck this tick (hit-marker + stagger cue).
		BroadcastHitConfirmed(SwingResult.ReceiversDamaged - Before, SwingResult.ContextTags);
	}
}

const UNexusHitDelivery* UNexusAbility_WeaponMelee::ResolveMeleeDelivery() const
{
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	TSubclassOf<UNexusHitDelivery> Class = Weapon ? Weapon->Melee.HitDelivery : nullptr;
	if (!Class)
	{
		Class = UNexusHitDelivery_MeleeSweep::StaticClass();
	}
	return GetDefault<UNexusHitDelivery>(Class);
}

float UNexusAbility_WeaponMelee::GetCooldownTotalDuration() const
{
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon) return Super::GetCooldownTotalDuration();

	float Spm = Weapon->Melee.SwingsPerMinute;
	if (const ANexusEquippedActor* Equipped = GetEquippedActor())
	{
		Spm = Equipped->GetEffectiveStat(NexusGameplayTags::Stat_Melee_SwingRate, Spm);
	}
	return Spm > 0.0f ? FMath::Max(0.0f, 60.0f / Spm) : 0.0f;
}

bool UNexusAbility_WeaponMelee::HasCooldown() const
{
	return GetCooldownTotalDuration() > 0.0f;
}

UNexusStaminaComponent* UNexusAbility_WeaponMelee::GetStamina() const
{
	const AActor* Owner = GetOwner();
	return Owner ? Owner->FindComponentByClass<UNexusStaminaComponent>() : nullptr;
}

float UNexusAbility_WeaponMelee::GetSwingStaminaCost(bool bHeavy) const
{
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	if (!Weapon) return 0.0f;

	float Cost = Weapon->Melee.StaminaCost;
	if (const ANexusEquippedActor* Equipped = GetEquippedActor())
	{
		Cost = Equipped->GetEffectiveStat(NexusGameplayTags::Stat_Melee_StaminaCost, Cost);
	}
	if (bHeavy) Cost *= FMath::Max(1.0f, Weapon->Melee.HeavyStaminaMultiplier);
	return FMath::Max(0.0f, Cost);
}

bool UNexusAbility_WeaponMelee::TickDurabilityAndMaybeBreak()
{
	const FNexusFragment_Weapon* Weapon = GetWeaponFragment();
	UNexusItemInstance* Instance = GetActiveInstance();
	if (!Weapon || !Instance || !Weapon->bHasMelee || !Weapon->Melee.bUsesDurability) return false;

	const float Wear = FMath::Max(0.0f, Weapon->Melee.DurabilityPerSwing);
	const float NewDurability = FMath::Max(0.0f,
		Instance->GetStat(NexusGameplayTags::Stat_Durability, 0.0f) - Wear);
	Instance->SetStat(NexusGameplayTags::Stat_Durability, NewDurability);

	if (NewDurability > 0.0f) return false;

	// Broke (RE4R-knife scarcity): remove the weapon from inventory. The equipment component
	// clears the slot in response (HandleInventoryItemRemoved), which removes this ability too.
#if !UE_BUILD_SHIPPING
	UE_LOG(LogNexusWeapon, Log, TEXT("[Melee] %s broke (durability exhausted)."),
		*GetNameSafe(GetActiveDefinition()));
#endif
	if (const AActor* Owner = GetOwner())
	{
		if (UNexusInventoryComponent* Inventory = Owner->FindComponentByClass<UNexusInventoryComponent>())
		{
			Inventory->RemoveInstance(Instance);
			return true;
		}
	}
	return false;
}

void UNexusAbility_WeaponMelee::FinishSwing()
{
	// Decrement durability for the completed swing; if it breaks, the weapon (and this
	// ability) are removed and we must not also CommitAbilityEnd on a torn-down state.
	if (TickDurabilityAndMaybeBreak()) return;
	CommitAbilityEnd();
}

void UNexusAbility_WeaponMelee::OnSaveStateRestored()
{
	Super::OnSaveStateRestored();

	bWindowOpen = false;
	bHeavyNext  = false;
	SwingResult = FNexusHitDeliveryResult{};
	if (IsActive())
	{
		ForceEndAbility();
	}
}
