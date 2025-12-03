// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "WCharacterBase.h"
#include "WPlayerCharacter.generated.h"


class UNiagaraSystem;
UCLASS()
class WGAS_API AWPlayerCharacter : public AWCharacterBase
{
	GENERATED_BODY()

public:
	AWPlayerCharacter();
	
	void Move(const FVector2d& MovementVector);
	void LookMouseCursor(const FVector& TargetLocation);
	void StopLookMouseCursor();
	void Dash();
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
protected:
	void InitAbilityInfo();

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* DashEffect;
	
	bool bIsDashing = false;
	
	UPROPERTY(EditDefaultsOnly)
	float DashCooldown{1.f};

	UPROPERTY(EditDefaultsOnly)
	float DashSpeed{5.f};



	void PlayDashEffect();

};
