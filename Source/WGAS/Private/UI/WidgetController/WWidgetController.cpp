// Copyright Deniz Yilmaz


#include "UI/WidgetController/WWidgetController.h"

void UWWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
	PlayerController = WidgetControllerParams.PlayerController;;
	PlayerState = WidgetControllerParams.PlayerState;
	AbilitySystemComponent = WidgetControllerParams.AbilitySystemComponent;;
	AttributeSet = WidgetControllerParams.AttributeSet;
}
