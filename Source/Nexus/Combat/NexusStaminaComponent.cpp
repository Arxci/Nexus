#include "NexusStaminaComponent.h"

UNexusStaminaComponent::UNexusStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNexusStaminaComponent::BeginPlay()
{
	Super::BeginPlay();
	Stamina = FMath::Clamp(Stamina <= 0.0f ? MaxStamina : Stamina, 0.0f, MaxStamina);
	TimeSinceSpend = RegenDelay; // start ready to regen
}

void UNexusStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Stamina >= MaxStamina) return;

	TimeSinceSpend += DeltaTime;
	if (TimeSinceSpend < RegenDelay || RegenPerSecond <= 0.0f) return;

	SetStamina(Stamina + RegenPerSecond * DeltaTime);
}

bool UNexusStaminaComponent::ConsumeStamina(float Amount)
{
	if (Amount <= 0.0f) return true;       // a free action always succeeds
	if (Stamina < Amount) return false;    // not enough — spend nothing

	TimeSinceSpend = 0.0f;                  // gate regen behind the delay again
	SetStamina(Stamina - Amount);
	return true;
}

void UNexusStaminaComponent::RestoreStamina(float Amount)
{
	if (Amount <= 0.0f) return;
	SetStamina(Stamina + Amount);
}

void UNexusStaminaComponent::SetStamina(float NewStamina)
{
	NewStamina = FMath::Clamp(NewStamina, 0.0f, MaxStamina);
	if (NewStamina == Stamina) return;

	const float Old = Stamina;
	Stamina = NewStamina;
	OnStaminaChanged.Broadcast(this, Old, Stamina);
}
