// Copyright Deniz Yilmaz


#include "AbilitySystem/WAbilitySystemComponent.h"

#include "WGameplayTags.h"

void UWAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UWAbilitySystemComponent::EffectApplied);
	
}

void UWAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                             const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	//Binded function: OverlayWidgetController->BindCallbacksToDependencies
	EffectAssetTags.Broadcast(TagContainer);
	
}
