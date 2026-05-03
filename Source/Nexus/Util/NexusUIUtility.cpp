#include "NexusUIUtility.h"

#include "CommonInputSubsystem.h"
#include "CommonInputBaseTypes.h"

#include "Engine/LocalPlayer.h"

//Input
FSlateBrush UNexusUIUtility::GetIconForFKey(UObject* WorldContextObject, FKey Key)
{
	FSlateBrush Brush;
	if (!WorldContextObject)
	{
		return Brush;
	}

	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
	{
		return Brush;
	}

	// Prefer the owning player when called from a widget; fall back to first PC.
	const APlayerController* PC = nullptr;
	if (const UWidget* Widget = Cast<UWidget>(WorldContextObject))
	{
		PC = Widget->GetOwningPlayer();
	}
	if (!PC)
	{
		PC = World->GetFirstPlayerController();
	}
	if (!PC)
	{
		return Brush;
	}

	const ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
	if (!LocalPlayer)
	{
		return Brush;
	}

	const UCommonInputSubsystem* CommonInput = LocalPlayer->GetSubsystem<UCommonInputSubsystem>();
	if (!CommonInput)
	{
		return Brush;
	}

	const UCommonInputPlatformSettings* PlatformSettings = UCommonInputPlatformSettings::Get();
	if (!PlatformSettings)
	{
		return Brush;
	}

	const ECommonInputType InputType = CommonInput->GetCurrentInputType();
	const FName GamepadName = CommonInput->GetCurrentGamepadName();

	PlatformSettings->TryGetInputBrush(Brush, Key, InputType, GamepadName);
	return Brush;
}


//Size box
void UNexusUIUtility::SetSizeBoxSize(USizeBox* Target, const FVector2D NewSize)
{
	if (!IsValid(Target))
	{
		return;
	}

	Target->SetWidthOverride(NewSize.X);
	Target->SetHeightOverride(NewSize.Y);
}


//Image
void UNexusUIUtility::SetImageBrushSize(UImage* Target, const FVector2D NewSize)
{
	if (!IsValid(Target))
	{
		return;
	}

	FSlateBrush NewBrush = Target->GetBrush();
	NewBrush.ImageSize = FVector2D(NewSize.X, NewSize.Y);
	Target->SetBrush(NewBrush);
}


//Interpolation
void UNexusUIUtility::InterpolateWidgetRenderOpacity(UWidget* Target, const float TargetOpacity, const float InterpSpeed)
{
	if (!IsValid(Target))
	{
		return;
	}

	const UWorld* World = Target->GetWorld();
	if (!World)
	{
		return;
	}

	const float DeltaTime = World->GetDeltaSeconds();
	const float CurrentOpacity = Target->GetRenderOpacity();
	const float NewOpacity = FMath::FInterpTo(CurrentOpacity, TargetOpacity, DeltaTime, InterpSpeed);
	Target->SetRenderOpacity(NewOpacity);
}