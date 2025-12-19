// Copyright Deniz Yilmaz


#include "Input/WInputConfig.h"

const UInputAction* UWInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FWInputAction& Input : AbilityInputActions)
	{
		if (Input.InputAction && Input.InputTag == InputTag)
		{
			return Input.InputAction;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Ability InputAction not found for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *InputTag.ToString(),*GetNameSafe(this));
	}
	return nullptr;
}
