// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WWidgetController.h"
#include "Controller/WPlayerController.h"
#include "WOverlayWidgetController.generated.h"

class UWUserWidget;
struct FOnAttributeChangeData;

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText MessageText = FText();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UWUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttributeMenuPressedSignature);


/**
 *
 * BlueprintType: an object can cast as this class
 * Blueprintable: can make blueprintclass from this class
 */
UCLASS(BlueprintType, Blueprintable)
class WGAS_API UWOverlayWidgetController : public UWWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbackDependencies() override;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangeSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangeSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangeSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangeSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangeSignature OnStaminaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangeSignature OnMaxStaminaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;

	UPROPERTY(BlueprintAssignable, Category="GAS|UI")
	FOnAttributeMenuPressedSignature OnAttributeMenuPressed;

	UFUNCTION(BlueprintCallable, Category="GAS|UI")
	FORCEINLINE bool IsAttributeMenuEnabled() {return bIsAttributeMenuEnabled;}

	//if bIsAttributeMenuEnabled true it will make it false or vise-versa
	UFUNCTION(BlueprintCallable, Category="GAS|UI")
	FORCEINLINE void SetAttributeMenuEnabled(){ bIsAttributeMenuEnabled = !bIsAttributeMenuEnabled;};
protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);

private:

	bool bIsAttributeMenuEnabled = false;
};

template <typename T>
T* UWOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}


