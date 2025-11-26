// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class WGAS_API UWUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	
protected:

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet(); //Call when widget controller set on widget 
};
