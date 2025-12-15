// Copyright Deniz Yilmaz


#include "AbilitySystem/Data/AttributeInfo.h"

FWAttributeInfo UAttributeInfo::FindAttributeInfoByTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FWAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Attribute not found with tag [%s] on AttributeInfo [%s]"),*AttributeTag.ToString(),*GetNameSafe(this));
	}
	return FWAttributeInfo();
}
