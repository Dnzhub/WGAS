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

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

protected:

	// Reliable: Even if package lost it guarantee will reach to client
	// Call in server but execute in client
	UFUNCTION(Client, Reliable)
	//Delegate binding for when an effect is applied
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec,
		FActiveGameplayEffectHandle ActiveEffectHandle);
};
