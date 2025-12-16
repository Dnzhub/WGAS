// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WHUD.generated.h"

class UAttributeMenuWidgetController;
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

	

	UWOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
	void InitOverlay(APlayerController* PC,ACharacter* CH, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:
	
private:

	UPROPERTY()
	TObjectPtr<UWUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWUserWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWOverlayWidgetController> OverlayWidgetControllerClass;
	
	UPROPERTY()
	TObjectPtr<UWOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
	
	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
};
