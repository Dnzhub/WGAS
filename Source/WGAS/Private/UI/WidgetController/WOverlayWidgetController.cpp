// Copyright Deniz Yilmaz


#include "UI/WidgetController/WOverlayWidgetController.h"

#include "AbilitySystem/WAttributeSet.h"

void UWOverlayWidgetController::BroadcastInitialValues()
{
	const UWAttributeSet* Attribute = CastChecked<UWAttributeSet>(AttributeSet);

	//Initialize attributes for first time
	OnHealthChanged.Broadcast(Attribute->GetHealth());
	OnMaxHealthChanged.Broadcast(Attribute->GetMaxHealth());
	OnManaChanged.Broadcast(Attribute->GetMana());
	OnMaxManaChanged.Broadcast(Attribute->GetMaxMana());
	
}

void UWOverlayWidgetController::BindCallbackDependencies()
{
	const UWAttributeSet* Attribute = CastChecked<UWAttributeSet>(AttributeSet);

	//Bind delegates for specific attributes
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		Attribute->GetHealthAttribute()).AddUObject(this,&UWOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	Attribute->GetMaxHealthAttribute()).AddUObject(this,&UWOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	Attribute->GetManaAttribute()).AddUObject(this,&UWOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	Attribute->GetMaxManaAttribute()).AddUObject(this,&UWOverlayWidgetController::MaxManaChanged);
}

void UWOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UWOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);

}
void UWOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UWOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}