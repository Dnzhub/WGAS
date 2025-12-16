// Copyright Deniz Yilmaz


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "Controller/WPlayerController.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
}

void UAttributeMenuWidgetController::BindCallbackDependencies()
{
	
	Cast<AWPlayerController>(PlayerController)->OnAttributeMenuPressed.AddLambda([this]()
	{
		OnAttributeMenuPressed.Broadcast();
	});
}
