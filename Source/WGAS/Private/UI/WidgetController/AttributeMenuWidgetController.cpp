// Copyright Deniz Yilmaz


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Controller/WPlayerController.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{

	check(AttributeInfo);

	for (auto Info : AttributeInfo.Get()->AttributeInformation)
	{
		BroadcastAttributeInfo(Info);
	}
}

void UAttributeMenuWidgetController::BindCallbackDependencies()
{
	
	Cast<AWPlayerController>(PlayerController)->OnAttributeMenuPressed.AddLambda([this]()
	{
		OnAttributeMenuPressed.Broadcast();
	});

	for (auto Info : AttributeInfo.Get()->AttributeInformation)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Info.AttributeGetter).AddLambda(
			[this,Info](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Info);
			});
	}
	
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FWAttributeInfo& Info)
{
	FWAttributeInfo NewInfo = Info;
	NewInfo.AttributeValue = Info.AttributeGetter.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(NewInfo);

	
}
