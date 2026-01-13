// Copyright Deniz Yilmaz


#include "AbilitySystem/Abilities/WMeleeAbility.h"

UAnimMontage* UWMeleeAbility::GetMontageByIndex(int32 index)
{
	if (MeleeAbilityMontages.IsValidIndex(index))
	{
		return MeleeAbilityMontages[index];
	}
	return nullptr;
}
