#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintHelpers.generated.h"

/**
 * 
 */
UCLASS()
class VRBOOKS_API UBlueprintHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "VRBooks|BlueprintHelpers")
	static void LoadPDF(const FString& Path, TArray<UTexture2D*>& BookPages);
};
