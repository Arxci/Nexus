#include "NexusProjectile.h"

#include "Components/SphereComponent.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Kismet/GameplayStatics.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Particles/ParticleSystem.h"

ANexusProjectile::ANexusProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->InitSphereRadius(6.0f);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionObjectType(ECC_WorldDynamic);
	Collision->SetCollisionResponseToAllChannels(ECR_Block);
	Collision->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	Collision->CanCharacterStepUpOn = ECB_No;
	SetRootComponent(Collision);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->bRotationFollowsVelocity = true;
	Movement->bShouldBounce            = false;
	Movement->ProjectileGravityScale   = 0.0f; // straight by default; a grenade BP authors gravity
	Movement->InitialSpeed             = 6000.0f;
	Movement->MaxSpeed                 = 6000.0f;

	InitialLifeSpan = 5.0f;
}

void ANexusProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (Collision)
	{
		Collision->OnComponentHit.AddDynamic(this, &ANexusProjectile::HandleHit);
	}
}

void ANexusProjectile::Launch(const FNexusHitDeliveryRequest& InRequest, const FVector& LaunchDir,
	const float Speed, const float LifeSeconds)
{
	Request = InRequest;
	Request.DamageFalloffCurve = nullptr; // never hold the fragment's curve across the flight

	if (Movement)
	{
		const float S = Speed > 0.0f ? Speed : Movement->InitialSpeed;
		Movement->InitialSpeed = S;
		Movement->MaxSpeed     = S;
		Movement->Velocity     = LaunchDir.GetSafeNormal() * S;
	}

	if (LifeSeconds > 0.0f)
	{
		SetLifeSpan(LifeSeconds);
	}

	// Ignore the wielder so the projectile can't immediately collide with the muzzle.
	if (AActor* IgnorePawn = Request.InstigatorPawn.Get())
	{
		if (Collision) Collision->IgnoreActorWhenMoving(IgnorePawn, true);
	}
}

void ANexusProjectile::HandleHit(UPrimitiveComponent* /*HitComp*/, AActor* OtherActor,
	UPrimitiveComponent* /*OtherComp*/, FVector /*NormalImpulse*/, const FHitResult& Hit)
{
	if (bResolved) return;

	// Never detonate on the wielder.
	if (OtherActor && (OtherActor == Request.Instigator.Get() || OtherActor == Request.InstigatorPawn.Get()))
	{
		return;
	}

	bResolved = true;

	// One uniform packet, routed through the SAME path as the trace strategies (weak-point
	// classification + ExtraContextTags included). Impulse along the travel direction.
	const FVector ImpulseDir = Movement ? Movement->Velocity.GetSafeNormal() : Request.Direction;
	FNexusHitDeliveryResult Result;
	UNexusHitDelivery::RouteDamage(Request, Hit, /*PreMultiplier*/ 1.0f, ImpulseDir, Result);

	if (UFXSystemAsset* FX = ImpactFX.Get() ? ImpactFX.Get() : ImpactFX.LoadSynchronous())
	{
		if (UParticleSystem* P = Cast<UParticleSystem>(FX))
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, P, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
		}
		else if (UNiagaraSystem* N = Cast<UNiagaraSystem>(FX))
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, N, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
		}
	}

	Destroy();
}
