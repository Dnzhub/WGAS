// Copyright Deniz Yilmaz


#include "AbilitySystem/WAbilitySystemComponent.h"

#include "WGameplayTags.h"
#include "AbilitySystem/Abilities/WGameplayAbility.h"

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
void UWAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> Ability : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability,1);
		if (const UWGameplayAbility* WAbility = Cast<UWGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(WAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
			//GiveAbilityAndActivateOnce(AbilitySpec);
		}
	
	}
}

void UWAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			//Tell ability that its input pressed
			//You can override InputPressed() function in GameplayAbility in its base class its empty
			//But you can override and do custom logic there
			AbilitySpecInputPressed(AbilitySpec);
			//Activate it if its currently not active already
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UWAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			//Tell ability that its input pressed
			//You can override InputPressed() function in GameplayAbility in its base class its empty
			//But you can override and do custom logic there
			AbilitySpecInputReleased(AbilitySpec);

			
		}
	}
}
