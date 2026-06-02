#include "Validation/NexusValidateContentCommandlet.h"

#include "Audit/NexusContentAudit.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"

DEFINE_LOG_CATEGORY_STATIC(LogNexusValidate, Log, All);

int32 UNexusValidateContentCommandlet::Main(const FString& Params)
{
	// A commandlet starts before the asset registry has scanned content; force a full
	// synchronous scan so the audit sees every item/attachment.
	IAssetRegistry& AssetRegistry =
		FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();
	AssetRegistry.SearchAllAssets(/*bSynchronousSearch=*/ true);

	const FNexusAuditResult Result = FNexusContentAudit::Run();

	for (const TSharedPtr<FNexusAuditFinding>& Finding : Result.Findings)
	{
		if (!Finding.IsValid())
		{
			continue;
		}
		const TCHAR* Severity =
			Finding->Severity == ENexusAuditSeverity::Error   ? TEXT("ERROR") :
			Finding->Severity == ENexusAuditSeverity::Warning ? TEXT("WARNING") : TEXT("INFO");
		UE_LOG(LogNexusValidate, Display, TEXT("[%s] %s"), Severity, *Finding->Message.ToString());
	}

	UE_LOG(LogNexusValidate, Display,
		TEXT("Nexus content audit: %d item(s), %d attachment(s), %d error(s), %d warning(s)."),
		Result.Items.Num(), Result.Attachments.Num(), Result.NumErrors, Result.NumWarnings);

	// Non-zero exit on errors fails the CI step; warnings/info don't break the build.
	return Result.NumErrors > 0 ? 1 : 0;
}
