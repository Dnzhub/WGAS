// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UWOverlayWidgetController;
class UWUserWidget;
struct FWidgetControllerParams;

/**
 * 
 */
UCLASS()
class WGAS_API AWHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<UWUserWidget> OverlayWidget;

	UWOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC,ACharacter* CH, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:
	
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWUserWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWOverlayWidgetController> OverlayWidgetControllerClass;
	
	UPROPERTY()
	TObjectPtr<UWOverlayWidgetController> OverlayWidgetController;
};
