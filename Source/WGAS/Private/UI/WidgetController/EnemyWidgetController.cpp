// Copyright Deniz Yilmaz


#include "UI/WidgetController/EnemyWidgetController.h"

#include "AbilitySystem/WAttributeSet.h"

void UEnemyWidgetController::BroadcastInitialValues()
{
	const UWAttributeSet* Attribute = CastChecked<UWAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(Attribute->GetHealth());
	OnMaxHealthChanged.Broadcast(Attribute->GetMaxHealth());

}

void UEnemyWidgetController::BindCallbackDependencies()
{
	const UWAttributeSet* Attribute = CastChecked<UWAttributeSet>(AttributeSet);

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
}
