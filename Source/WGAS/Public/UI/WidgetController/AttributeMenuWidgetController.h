// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "WWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttributeMenuPressedSignature);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class WGAS_API UAttributeMenuWidgetController : public UWWidgetController
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category="GAS|UI")
	FOnAttributeMenuPressedSignature OnAttributeMenuPressed;
	
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbackDependencies() override;

	
	UFUNCTION(BlueprintCallable, Category="GAS|UI")
	FORCEINLINE bool IsAttributeMenuEnabled() {return bIsAttributeMenuEnabled;}

	//if bIsAttributeMenuEnabled true it will make it false or vise-versa
	UFUNCTION(BlueprintCallable, Category="GAS|UI")
	FORCEINLINE void SetAttributeMenuEnabled(){ bIsAttributeMenuEnabled = !bIsAttributeMenuEnabled;};

private:
	bool bIsAttributeMenuEnabled = false;
};
