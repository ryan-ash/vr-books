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

// this is a dirty copy paste from engine born out of inability to get directory list via file manager and to use internal FileMatch class
// sorry, my future self... yet this works and stays for now
class FCustomFileMatch : public IPlatformFile::FDirectoryVisitor
{
public:
    TArray<FString>& Result;
    FRWLock ResultLock;
    FString WildCard;
    bool bFiles;
    bool bDirectories;
    bool bStoreFullPath;
    FCustomFileMatch(TArray<FString>& InResult, const FString& InWildCard, bool bInFiles, bool bInDirectories, bool bInStoreFullPath = false)
        : IPlatformFile::FDirectoryVisitor(EDirectoryVisitorFlags::ThreadSafe)
        , Result(InResult)
        , WildCard(InWildCard)
        , bFiles(bInFiles)
        , bDirectories(bInDirectories)
        , bStoreFullPath(bInStoreFullPath)
    {
    }
    virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)
    {
        if ((bIsDirectory && bDirectories) || (!bIsDirectory && bFiles))
        {
            FString Filename = FPaths::GetCleanFilename(FilenameOrDirectory);
            if (Filename.MatchesWildcard(WildCard))
            {
                FString FullPath = bStoreFullPath ? FString(FilenameOrDirectory) : MoveTemp(Filename);
                FWriteScopeLock ScopeLock(ResultLock);
                Result.Add(MoveTemp(FullPath));
            }
        }
        return true;
    }
};