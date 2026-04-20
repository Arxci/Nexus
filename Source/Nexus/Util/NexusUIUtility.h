#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NexusUIUtility.generated.h"

UCLASS()
class NEXUS_API UNexusUIUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//Input
	UFUNCTION(BlueprintPure, Category = "UI|Input", meta = (WorldContext = "WorldContextObject"))
	static FSlateBrush GetIconForFKey(UObject* WorldContextObject, FKey Key);

	
	//Size Box
	UFUNCTION(BlueprintCallable, Category = "UI|SizeBox", meta = (WorldContext = "WorldContextObject"))
	static void SetSizeBoxSize(USizeBox* Target, const FVector2D NewSize);

	
	//Image
	UFUNCTION(BlueprintCallable, Category = "UI|Image", meta = (WorldContext = "WorldContextObject"))
	static void SetImageBrushSize(UImage* Target, const FVector2D NewSize);


	//Interpolation
	UFUNCTION(BlueprintCallable, Category = "UI|Interpolation", meta = (WorldContext = "WorldContextObject"))
	static void InterpolateWidgetRenderOpacity(UWidget* Target, const float TargetOpacity, const float InterpSpeed);
};