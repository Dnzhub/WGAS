// Copyright Deniz Yilmaz


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"

#include "AbilitySystem/WAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef.AttributeToCapture = UWAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	/**Capture it when gameplay effect spec first created : true
	 * or
	 * when effect is applied  : false ?
	 **/
	VigorDef.bSnapshot = false;

	//Add attributes to capture in MMC array
	RelevantAttributesToCapture.Add(VigorDef);
	
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{

	//Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	
	//Get attributes and attribute magnitudes
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Vigor{0.f};
	GetCapturedAttributeMagnitude(VigorDef,Spec,EvaluateParameters,Vigor);

	Vigor = FMath::Max(Vigor,0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	//Return custom calculation as you like
	return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;	
}
