// Copyright Deniz Yilmaz


#include "UI/HUD/WHUD.h"
#include "UI/Widget/WUserWidget.h"
#include "UI/WidgetController/WOverlayWidgetController.h"

UWOverlayWidgetController* AWHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{

	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UWOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbackDependencies();
	}
	return OverlayWidgetController;
}

void AWHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{

	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class is NULL, fill out BP_HUD class"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class is NULL, fill out BP_HUD class"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UWUserWidget>(Widget); //Construct overlay widget
	
	const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
	UWOverlayWidgetController* WidgetController =  GetOverlayWidgetController(WidgetControllerParams); //Construct overlay widget controller
	
	OverlayWidget->SetWidgetController(WidgetController); //Set that controller for the widget
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();
}

