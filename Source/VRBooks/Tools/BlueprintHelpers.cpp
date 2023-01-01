#include "BlueprintHelpers.h"

#include <Runtime/Launch/Resources/Version.h>
#include <HAL/PlatformProcess.h>

void UBlueprintHelpers::LoadPDF(const FString& Path, TArray<UTexture2D*>& BookPages)
{
    // Set the command line arguments for the process
    TArray<FString> Arguments;
    Arguments.Add(FString("-density 300"));
    Arguments.Add(Path);
    Arguments.Add(FString("current_book.bmp"));

    // Create the process and execute the command line utility
    FString CommandLine = "convert.exe";
    FString ArgumentsString;
    for (const FString& Argument : Arguments)
    {
        ArgumentsString += Argument;
    }
    FProcHandle ProcessHandle = FPlatformProcess::CreateProc(*CommandLine, *ArgumentsString, true, false, false, nullptr, 0, nullptr, nullptr);

    // Wait for the process to finish
    FPlatformProcess::WaitForProc(ProcessHandle);

    // Get the return code from the process
    int32 ReturnCode;
    FPlatformProcess::GetProcReturnCode(ProcessHandle, &ReturnCode);

    // Do something with the return code
    if (ReturnCode == 0)
    {
        // Process completed successfully
    }
    else
    {
        // Process failed with an error
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
    IFileManager::Get().FindFiles(Directories, *Directory, true, false);
    return Directories;
}
