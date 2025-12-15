// Copyright Deniz Yilmaz


#include "AbilitySystem/WAbilitySystemComponent.h"

#include "WGameplayTags.h"

void UWAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UWAbilitySystemComponent::EffectApplied);
	const FWGameplayTags& GameplayTags = FWGameplayTags::Get();
	GEngine->AddOnScreenDebugMessage(-1, 5.f,FColor::Orange,
		FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_Armor.ToString()));
}

void UWAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                             const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	//Binded function: OverlayWidgetController->BindCallbacksToDependencies
	EffectAssetTags.Broadcast(TagContainer);
	
}
