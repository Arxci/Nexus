#pragma once

#include "CoreMinimal.h"

#include "NexusAttachmentFragment.generated.h"

class UNexusAttachmentDefinition;


/**
 * Base struct for attachment fragments. Mirrors FNexusItemFragment: composition
 * over inheritance, attachment-type-specific data lives in concrete subclasses
 * (e.g. FNexusAttachmentFragment_Magazine for loaded/empty mesh swap data) so
 * UNexusAttachmentDefinition stays generic across scopes, foregrips, magazines,
 * future flashlights, lasers, etc.
 *
 * Designers compose attachments by adding fragments in the editor. Code looks
 * up a specific fragment via UNexusAttachmentDefinition::FindFragment<T>().
 */
USTRUCT(BlueprintType, meta = (Hidden))
struct NEXUS_API FNexusAttachmentFragment
{
	GENERATED_BODY()

	virtual ~FNexusAttachmentFragment() = default;
};