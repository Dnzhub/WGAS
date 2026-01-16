// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "WWidgetController.h"
#include "EnemyWidgetController.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyAttributeChangeSignature, float, NewValue);

UCLASS(BlueprintType, Blueprintable)
class WGAS_API UEnemyWidgetController : public UWWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbackDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnEnemyAttributeChangeSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnEnemyAttributeChangeSignature OnMaxHealthChanged;
};
