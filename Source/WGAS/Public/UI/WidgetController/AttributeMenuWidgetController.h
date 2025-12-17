// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "WWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FWAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttributeMenuPressedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FWAttributeInfo&, Info);

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

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;
	
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbackDependencies() override;

	
	UFUNCTION(BlueprintCallable, Category="GAS|UI")
	FORCEINLINE bool IsAttributeMenuEnabled() {return bIsAttributeMenuEnabled;}

	//if bIsAttributeMenuEnabled true it will make it false or vise-versa
	UFUNCTION(BlueprintCallable, Category="GAS|UI")
	FORCEINLINE void SetAttributeMenuEnabled(){ bIsAttributeMenuEnabled = !bIsAttributeMenuEnabled;};

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;
	
private:
	bool bIsAttributeMenuEnabled = false;
	void BroadcastAttributeInfo(const FWAttributeInfo& Info);
};
