#pragma once

#include "CoreMinimal.h"
#include "Commandlets/Commandlet.h"
#include "NexusValidateContentCommandlet.generated.h"

/**
 * Headless content validation for CI. Runs the full FNexusContentAudit and returns a
 * non-zero exit code if any errors were found, so a pull request that adds broken content
 * fails the build instead of surfacing in playtest.
 *
 *     UnrealEditor-Cmd.exe <Project>.uproject -run=NexusValidateContent
 */
UCLASS()
class UNexusValidateContentCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	virtual int32 Main(const FString& Params) override;
};
