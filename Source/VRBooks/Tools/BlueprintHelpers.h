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

	UFUNCTION(BlueprintCallable, Category = "VRBooks|BlueprintHelpers")
	static TArray<FString> GetFilesInDirectory(const FString& Directory, const FString& FileExtension);

	UFUNCTION(BlueprintCallable, Category = "VRBooks|BlueprintHelpers")
	static TArray<FString> GetDirectoriesInDirectory(const FString& Directory);
};
