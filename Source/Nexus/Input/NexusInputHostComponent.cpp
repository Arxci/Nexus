#include "NexusInputHostComponent.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

#include "Nexus/Nexus.h"
#include "Nexus/Input/NexusInputComponent.h"
#include "Nexus/Input/NexusInputContext.h"
#include "Nexus/Input/NexusInputManager.h"

UNexusInputHostComponent::UNexusInputHostComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNexusInputHostComponent::BeginPlay()
{
	Super::BeginPlay();

	// The project's game mode guarantees BeginPlay runs after possession, so a locally
	// controlled hero is already possessed here. (Possession changes after this come through
	// NotifyControllerChanged.) Guarded by bInputSetUp so it's harmless if possession already
	// wired us.
	if (IsLocallyControlledPlayer())
	{
		SetUpInput();
	}
}

void UNexusInputHostComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	TearDownInput();
	Super::EndPlay(EndPlayReason);
}

void UNexusInputHostComponent::NotifyControllerChanged()
{
	// Re-evaluate from scratch: drop any prior wiring, then set up if the new controller is a
	// local player. Teardown is a no-op when nothing was set up.
	TearDownInput();
	if (IsLocallyControlledPlayer())
	{
		SetUpInput();
	}
}

bool UNexusInputHostComponent::IsLocallyControlledPlayer() const
{
	const APawn* Pawn = Cast<APawn>(GetOwner());
	const APlayerController* PC = Pawn ? Cast<APlayerController>(Pawn->GetController()) : nullptr;
	return PC && PC->IsLocalController();
}

void UNexusInputHostComponent::SetUpInput()
{
	if (bInputSetUp)
	{
		return;
	}

	APawn* Pawn = Cast<APawn>(GetOwner());
	APlayerController* PC = Pawn ? Cast<APlayerController>(Pawn->GetController()) : nullptr;
	UNexusInputManager* Manager = UNexusInputManager::GetForPawn(Pawn);
	if (!PC || !Manager)
	{
		return;
	}

	// Create the binder and register it. The hero overrides no input function — this
	// component owns it all.
	Binder = NewObject<UNexusInputComponent>(Pawn, UNexusInputComponent::StaticClass(), TEXT("NexusInputComponent"));
	Binder->RegisterComponent();

	// Register first so the manager's active set is populated, then bind it immediately, then
	// push onto the controller's input stack so Enhanced Input routes through it.
	TArray<UNexusInputContext*> Contexts;
	Contexts.Reserve(DefaultContexts.Num());
	for (const TObjectPtr<UNexusInputContext>& Context : DefaultContexts)
	{
		if (Context)
		{
			Contexts.Add(Context);
		}
	}
	Manager->RegisterInputPawn(Pawn, Contexts);
	Binder->InitializeBinder(Manager);
	PC->PushInputComponent(Binder);

	BoundController = PC;
	BoundManager = Manager;
	bInputSetUp = true;

#if !UE_BUILD_SHIPPING
	UE_LOG(LogNexusInput, Verbose, TEXT("[Input] Host set up input for %s (%d default context(s))."),
		*GetNameSafe(Pawn), Contexts.Num());
#endif
}

void UNexusInputHostComponent::TearDownInput()
{
	if (!bInputSetUp)
	{
		return;
	}

	if (UNexusInputManager* Manager = BoundManager.Get())
	{
		if (APawn* Pawn = Cast<APawn>(GetOwner()))
		{
			Manager->UnregisterInputPawn(Pawn);
		}
	}

	if (Binder)
	{
		if (APlayerController* PC = BoundController.Get())
		{
			PC->PopInputComponent(Binder);
		}
		Binder->TearDownBinder();
		Binder->DestroyComponent();
		Binder = nullptr;
	}

	BoundController = nullptr;
	BoundManager = nullptr;
	bInputSetUp = false;
}
