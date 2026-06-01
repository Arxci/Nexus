#include "NexusHitDelivery.h"

#include "Curves/CurveFloat.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"

#include "Nexus/Combat/NexusDamageContext.h"
#include "Nexus/Combat/NexusDamageReceiverInterface.h"
#include "Nexus/NexusGameplayTags.h"

namespace
{
	// Source-side weak-point classification thresholds, keyed off the receiver's own bone
	// multiplier (authored in UNexusHealthComponent::BoneDamageMultipliers). A weak point
	// reads as Critical; the strongest weak point (typically the head) also reads as a
	// Headshot. Data-driven — no bone-name strings, so any rig works by authoring multipliers.
	constexpr float NexusCriticalBoneMultiplier = 1.5f;
	constexpr float NexusHeadshotBoneMultiplier = 2.0f;
}

AActor* FNexusHitDeliveryRequest::GetContextActor() const
{
	if (AActor* P = InstigatorPawn.Get()) return P;
	if (AActor* I = Instigator.Get())     return I;
	return Causer.Get();
}

UWorld* FNexusHitDeliveryRequest::ResolveWorld() const
{
	const AActor* Context = GetContextActor();
	return Context ? Context->GetWorld() : nullptr;
}

bool UNexusHitDelivery::RouteDamage(const FNexusHitDeliveryRequest& Request, const FHitResult& Hit,
	const float PreMultiplier, const FVector& ImpulseDir, FNexusHitDeliveryResult& OutResult)
{
	AActor* HitActor = Hit.GetActor();
	if (!HitActor || !HitActor->Implements<UNexusDamageReceiver>()) return false;

	FNexusDamageContext Ctx;
	Ctx.Instigator    = Request.Instigator.Get();
	Ctx.Causer        = Request.Causer.Get();
	Ctx.DamageTypeTag = Request.DamageTypeTag;
	Ctx.BaseDamage    = Request.BaseDamage;
	Ctx.HitResult     = Hit;

	// Pre-resistance multiplier: delivery-specific scaling (PreMultiplier) × distance
	// falloff. Falloff is measured from the aim origin to the impact, matching the prior
	// inline hitscan behavior; a strategy with no curve (melee) leaves it at 1.
	float Multiplier = PreMultiplier;
	if (Request.DamageFalloffCurve)
	{
		const FRichCurve* Curve = Request.DamageFalloffCurve->GetRichCurveConst();
		if (Curve && Curve->GetNumKeys() > 0)
		{
			const float Distance = (Hit.ImpactPoint - Request.Origin).Size();
			Multiplier *= Curve->Eval(Distance, 1.0f);
		}
	}
	Ctx.Multiplier = Multiplier;

	FVector Dir = ImpulseDir;
	if (Dir.IsNearlyZero()) Dir = Request.Direction;
	Ctx.ImpulseDirection = Dir.GetSafeNormal();
	Ctx.ImpulseMagnitude = Request.ImpulseMagnitude;

	// Delivery-specific tags first (e.g. a melee Stagger), then source-side weak-point
	// classification on top: ask the receiver for the hit bone's multiplier (it owns the
	// numeric weak points) and stamp branchable ContextTags so AI / FX / HUD can react.
	// The receiver still applies the numeric multiply itself — no double counting here.
	Ctx.ContextTags.AppendTags(Request.ExtraContextTags);

	const float BoneMult = INexusDamageReceiver::Execute_GetBoneDamageMultiplier(HitActor, Hit.BoneName);
	if (BoneMult >= NexusHeadshotBoneMultiplier)
	{
		Ctx.ContextTags.AddTag(NexusGameplayTags::Damage_Context_Headshot);
		Ctx.ContextTags.AddTag(NexusGameplayTags::Damage_Context_Critical);
	}
	else if (BoneMult >= NexusCriticalBoneMultiplier)
	{
		Ctx.ContextTags.AddTag(NexusGameplayTags::Damage_Context_Critical);
	}

	INexusDamageReceiver::Execute_ReceiveDamage(HitActor, Ctx);
	++OutResult.ReceiversDamaged;
	OutResult.ContextTags.AppendTags(Ctx.ContextTags); // surface the cue for the attacker-side hit-marker
	return true;
}
