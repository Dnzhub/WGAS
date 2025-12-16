// Copyright Deniz Yilmaz


#include "UI/WidgetController/WOverlayWidgetController.h"

#include "AbilitySystem/WAbilitySystemComponent.h"
#include "AbilitySystem/WAttributeSet.h"
#include "Controller/WPlayerController.h"

void UWOverlayWidgetController::BroadcastInitialValues()
{
	const UWAttributeSet* Attribute = CastChecked<UWAttributeSet>(AttributeSet);

	//Initialize attributes for first time
	OnHealthChanged.Broadcast(Attribute->GetHealth());
	OnMaxHealthChanged.Broadcast(Attribute->GetMaxHealth());
	OnManaChanged.Broadcast(Attribute->GetMana());
	OnMaxManaChanged.Broadcast(Attribute->GetMaxMana());
	OnStaminaChanged.Broadcast(Attribute->GetStamina());
	OnMaxStaminaChanged.Broadcast(Attribute->GetMaxStamina());
	
}

void UWOverlayWidgetController::BindCallbackDependencies()
{
	const UWAttributeSet* Attribute = CastChecked<UWAttributeSet>(AttributeSet);

	//Bind delegates for specific attributes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	Attribute->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnHealthChanged.Broadcast(Data.NewValue);
	});

	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	Attribute->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	Attribute->GetManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnManaChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	Attribute->GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxManaChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	Attribute->GetStaminaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnStaminaChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	Attribute->GetMaxStaminaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxStaminaChanged.Broadcast(Data.NewValue);
	});


	
		

	Cast<UWAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
	[this](const FGameplayTagContainer& AssetTags)
	{
		for (const FGameplayTag& Tag : AssetTags)
		{
			//"Message.HealthPotion".MatchesTag("Message) will return true
			//"Message".MatchesTag("Message.HealthPotion) will return false
			FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
			if (Tag.MatchesTag(MessageTag))
			{
				const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
				MessageWidgetRowDelegate.Broadcast(*Row);
			}
		}	
	});
}




