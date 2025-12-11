// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxStamina.generated.h"

/**
 * 
 */
UCLASS()
class WGAS_API UMMC_MaxStamina : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_MaxStamina();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	//Capture an attribute
	FGameplayEffectAttributeCaptureDefinition VigorDef;
};
