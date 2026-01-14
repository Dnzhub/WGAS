// Copyright Deniz Yilmaz


#include "AbilitySystem/Abilities/WMeleeAbility.h"

#include "Character/WPlayerCharacter.h"

UAnimMontage* UWMeleeAbility::GetMontageByIndex(int32 index)
{
	if (MeleeAbilityMontages.IsValidIndex(index))
	{
		return MeleeAbilityMontages[index];
	}
	return nullptr;
}

bool UWMeleeAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)) return false;

	if (ActorInfo && ActorInfo->AvatarActor.IsValid())
	{
		if (AWPlayerCharacter* Character = Cast<AWPlayerCharacter>(ActorInfo->AvatarActor.Get()))
		{
			if (Character->IsAiming()) return false;
		}
	}
	
	return true;
}
