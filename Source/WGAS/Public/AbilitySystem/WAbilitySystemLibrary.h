// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WAbilitySystemLibrary.generated.h"

class UAttributeMenuWidgetController;
class UWOverlayWidgetController;
/**
 * 
 */
UCLASS()
class WGAS_API UWAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "AbilitySystemLibrary/WidgetController")
	static UWOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "AbilitySystemLibrary/WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
};
