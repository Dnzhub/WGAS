// Copyright Deniz Yilmaz


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"

#include "AbilitySystem/WAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UWAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	/**Capture it when gameplay effect spec first created : true
	 * or
	 * when effect is applied  : false ?
	 **/
	IntelligenceDef.bSnapshot = false;

	//Add attributes to capture in MMC array
	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	
	//Get attributes and attribute magnitudes
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Intelligence{0.f};
	GetCapturedAttributeMagnitude(IntelligenceDef,Spec,EvaluateParameters,Intelligence);

	Intelligence = FMath::Max(Intelligence,0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	//Return custom calculation as you like
	return 50.f + 1.5f * Intelligence + 15.f * PlayerLevel;
}
