#include "BlueprintHelpers.h"

#include <Runtime/Launch/Resources/Version.h>
#include <HAL/PlatformProcess.h>
#include <Misc/Paths.h>

void UBlueprintHelpers::LoadPDF(const FString& Path, TArray<UTexture2D*>& BookPages)
{
    FString FileNameWithoutExtension = FPaths::GetBaseFilename(Path);

    // Set the command line arguments for the process
    TArray<FString> Arguments;
    Arguments.Add(FString("-density 300"));
    FString WrappedPath = FString::Printf(TEXT("\"%s\""), *Path);
    Arguments.Add(WrappedPath);
    FString WrappedFileName = FString::Printf(TEXT("\"%s.bmp\""), *FileNameWithoutExtension);
    Arguments.Add(WrappedFileName);

    // Create the process and execute the command line utility
    FString CommandLine = "convert.exe";
    FString ArgumentsString;
    for (const FString& Argument : Arguments)
    {
        ArgumentsString += Argument + " ";
    }
    FString CommandLineWithArguments = CommandLine + " " + ArgumentsString;
    
    // TODO: FIX THIS

    FProcHandle ProcessHandle = FPlatformProcess::CreateProc(*CommandLineWithArguments, TEXT(""), false, false, false, 0, 0, nullptr, nullptr, nullptr);

    // Wait for the process to finish
    FPlatformProcess::WaitForProc(ProcessHandle);

    // Get the return code from the process
    int32 ReturnCode;
    FPlatformProcess::GetProcReturnCode(ProcessHandle, &ReturnCode);

    // Do something with the return code
    if (ReturnCode == 0)
    {
        const auto AllTargetFiles = GetFilesInDirectory(FileNameWithoutExtension, FString(".bmp"));
        for (const auto& TargetFile : AllTargetFiles)
        {
            BookPages.Add(LoadObject<UTexture2D>(nullptr, *TargetFile));
        }

        UE_LOG(LogTemp, Warning, TEXT("Book imported successfully: %s [%d]"), *Path, BookPages.Num());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Couldn't import PDF: %s"), *Path);
    }
}

TArray<FString> UBlueprintHelpers::GetFilesInDirectory(const FString& Directory, const FString& FileExtension)
{
    TArray<FString> Files;
    IFileManager::Get().FindFiles(Files, *Directory, *FileExtension);
    return Files;
}

TArray<FString> UBlueprintHelpers::GetDirectoriesInDirectory(const FString& Directory)
{
    TArray<FString> Directories;
    FCustomFileMatch FileMatch(Directories, TEXT("*"), false, true);
	IFileManager::Get().IterateDirectory(*FPaths::GetPath(Directory), FileMatch);
    return Directories;
}
