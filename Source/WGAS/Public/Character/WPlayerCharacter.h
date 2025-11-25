// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "WCharacterBase.h"
#include "WPlayerCharacter.generated.h"



UCLASS()
class WGAS_API AWPlayerCharacter : public AWCharacterBase
{
	GENERATED_BODY()

public:
	AWPlayerCharacter();

	void Move(const FVector2d& MovementVector);
	void LookMouseCursor(const FVector& TargetLocation);
	void StopLookMouseCursor();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
protected:
	void InitAbilityInfo();
};
