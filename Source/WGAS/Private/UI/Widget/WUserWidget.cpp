// Copyright Deniz Yilmaz


#include "UI/Widget/WUserWidget.h"

void UWUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet(); 
}
