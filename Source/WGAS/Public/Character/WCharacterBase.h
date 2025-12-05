// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "WCharacterBase.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class WGAS_API AWCharacterBase : public ACharacter, public IAbilitySystemInterface
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
	TSubclassOf<UGameplayEffect>  StaminaOvertimeGEClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect> StaminaConsumptionGEClass;
	
	void ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
