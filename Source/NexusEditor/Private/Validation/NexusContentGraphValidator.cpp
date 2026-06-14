#include "Validation/NexusContentGraphValidator.h"

#include "Audit/NexusContentAudit.h"
#include "Misc/DataValidation.h"

#include "Nexus/Inventory/NexusItemDefinition.h"
#include "Nexus/Equipment/Attachments/NexusAttachmentDefinition.h"

#define LOCTEXT_NAMESPACE "NexusContentGraphValidator"

bool UNexusContentGraphValidator::CanValidateAsset_Implementation(
	const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext) const
{
	return InAsset != nullptr
		&& (InAsset->IsA<UNexusItemDefinition>() || InAsset->IsA<UNexusAttachmentDefinition>());
}

EDataValidationResult UNexusContentGraphValidator::ValidateLoadedAsset_Implementation(
	const FAssetData& InAssetData, UObject* InAsset, FDataValidationContext& InContext)
{
	// One shared brain: the per-asset findings are exactly what the project-wide audit and
	// the live windows compute, so "Validate Assets" can never disagree with the dashboard.
	// The context is cached, so a "Validate All" pass scans the project a single time.
	const FNexusAuditContext& Context = FNexusContentAudit::GetCachedContext();

	TArray<FNexusAuditFinding> Findings;
	if (const UNexusItemDefinition* Item = Cast<UNexusItemDefinition>(InAsset))
	{
		FNexusContentAudit::AuditItem(Item, Context, Findings);
	}
	else if (const UNexusAttachmentDefinition* Attachment = Cast<UNexusAttachmentDefinition>(InAsset))
	{
		FNexusContentAudit::AuditAttachment(Attachment, Context, Findings);
	}
	else
	{
		return EDataValidationResult::NotValidated;
	}

	// Error gates (fails Validate Assets / CI); Warning surfaces but doesn't block; Info is
	// log-only and left off the validation result to keep the panel signal-to-noise high.
	bool bAnyError = false;
	for (const FNexusAuditFinding& Finding : Findings)
	{
		if (Finding.Severity == ENexusAuditSeverity::Error)
		{
			AssetFails(InAsset, Finding.Message);
			bAnyError = true;
		}
		else if (Finding.Severity == ENexusAuditSeverity::Warning)
		{
			// Route warnings through the validation context (the codebase's established
			// pattern, see UNexusNamingValidator) rather than AssetWarning, whose signature
			// has varied across engine versions.
			InContext.AddWarning(Finding.Message);
		}
	}

	if (!bAnyError)
	{
		AssetPasses(InAsset);
		return EDataValidationResult::Valid;
	}
	return EDataValidationResult::Invalid;
}

#undef LOCTEXT_NAMESPACE
