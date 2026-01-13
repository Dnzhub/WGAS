// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "WCharacterBase.h"
#include "WPlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaConsumeSignature);

class UNiagaraSystem;
UCLASS()
class WGAS_API AWPlayerCharacter : public AWCharacterBase
{
	GENERATED_BODY()

public:
	AWPlayerCharacter();
	
	void Move(const FVector2d& MovementVector);

	virtual void FaceToTarget_Implementation(const FVector& TargetLocation,float InterpSpeed) override;
	virtual void StopFaceToTarget_Implementation() override;

	void Dash();
	virtual void ConsumeStamina() override;
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnStaminaConsumeSignature OnStaminaConsume;

	/** Combat Interface **/

	virtual int32 GetPlayerLevel() override;
	/** End Combat Interface **/
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* DashEffect;
	
	bool bIsDashing = false;
	
	UPROPERTY(EditDefaultsOnly)
	float DashCooldown{1.f};

	UPROPERTY(EditDefaultsOnly)
	float DashSpeed{5.f};

	UPROPERTY(EditDefaultsOnly)
	float StaminaCost{20.f};
	
	void PlayDashEffect();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool IsAiming() {return bIsAiming;}


private:
	virtual void InitAbilityInfo() override;

	bool bIsAiming = false;
};
