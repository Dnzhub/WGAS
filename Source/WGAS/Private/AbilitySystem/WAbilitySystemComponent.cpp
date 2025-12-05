// Copyright Deniz Yilmaz


#include "AbilitySystem/WAbilitySystemComponent.h"

void UWAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,& UWAbilitySystemComponent::EffectApplied);
}

void UWAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                             const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	for (const FGameplayTag& Tag : TagContainer)
	{
		//TODO: Broadcast the tag to the widget controller
		const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Msg);
	}
}
