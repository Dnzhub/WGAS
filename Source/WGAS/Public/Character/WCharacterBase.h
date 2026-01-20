// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "WCharacterBase.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class WGAS_API AWCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AWCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityInfo();

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect>  StaminaGenerationGEClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect> StaminaConsumptionGEClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
	
	virtual void InitializeDefaultAttributes() const;
	virtual void ConsumeStamina();

	/*
	 * Params:
	 * GameplayEffectClass -> Adds any gameplayeffect to character
	 * ApplySelf: If true GE spec will apply to self, otherwise it will apply spec to target
	 */
	void ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass,float level = 1) const;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponSocketName = "WeaponHandSocket";
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;

	virtual FVector GetCombatSocketLocation() override;

	virtual void FaceToTarget_Implementation(const FVector& TargetLocation, float InterpSpeed) override;
	virtual void StopFaceToTarget_Implementation() override;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	void AddCharacterAbilities();
private:

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
