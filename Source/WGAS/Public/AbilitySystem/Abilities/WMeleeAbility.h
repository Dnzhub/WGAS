// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "WGameplayAbility.h"
#include "WMeleeAbility.generated.h"

/**
 * 
 */
UCLASS()
class WGAS_API UWMeleeAbility : public UWGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TArray<class UAnimMontage*> MeleeAbilityMontages;

	UPROPERTY(EditAnywhere, Category = "Combo")
	float LastAbilityUsingTime{0.0f};

	UFUNCTION(BlueprintCallable, Category = "Animation")
	UAnimMontage* GetMontageByIndex(int32 index);  
};
