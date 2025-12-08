// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags,const FGameplayTagContainer& /*AssetTags*/)

/**
 * 
 */
UCLASS()
class WGAS_API UWAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	//Called when abilty system component completely set in PlayerCharacter->InitAbilityActorInfo() and EnemyCharacter
	void AbilityActorInfoSet();

	FEffectAssetTags EffectAssetTags;
	
protected:

	
	//Delegate binding for when an effect is applied
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec,
		FActiveGameplayEffectHandle ActiveEffectHandle);
};
