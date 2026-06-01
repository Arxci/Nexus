#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "Nexus/Weapon/HitDelivery/NexusHitDelivery.h" // FNexusHitDeliveryRequest

#include "NexusProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UFXSystemAsset;


/**
 * Minimal projectile spawned by UNexusHitDelivery_Projectile. It carries the delivery
 * request and, on its first blocking hit, routes the SAME FNexusDamageContext as the
 * trace strategies through UNexusHitDelivery::RouteDamage — so a projectile weapon ends
 * in one uniform packet exactly like hitscan and melee. Self-contained presentation:
 * authors its own impact FX. A grenade / bolt / flame round is a Blueprint subclass
 * (mesh, FX, gravity, speed) — no new C++.
 */
UCLASS(Blueprintable)
class NEXUS_API ANexusProjectile : public AActor
{
	GENERATED_BODY()

public:
	ANexusProjectile();

	/**
	 * Launch: capture the delivery request (the fragment's falloff curve is dropped so
	 * nothing is held across the flight), aim the movement along LaunchDir at Speed, and
	 * ignore the wielder. On its first blocking hit it routes damage + spawns impact FX
	 * and destroys itself.
	 */
	void Launch(const FNexusHitDeliveryRequest& InRequest, const FVector& LaunchDir, float Speed, float LifeSeconds);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	TObjectPtr<USphereComponent> Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	TObjectPtr<UProjectileMovementComponent> Movement;

	/** Impact FX spawned at the hit point (authored on the projectile Blueprint). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile",
		meta = (AssetBundles = "Equipped"))
	TSoftObjectPtr<UFXSystemAsset> ImpactFX;

private:
	FNexusHitDeliveryRequest Request;
	bool bResolved = false;
};
