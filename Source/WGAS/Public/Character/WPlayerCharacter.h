// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "WCharacterBase.h"
#include "WPlayerCharacter.generated.h"

#define ECC_Cursor ECC_GameTraceChannel1

UCLASS()
class WGAS_API AWPlayerCharacter : public AWCharacterBase
{
	GENERATED_BODY()

public:
	AWPlayerCharacter();

	void Move(const FVector2d& MovementVector);
	void LookMouseCursor(const FVector& TargetLocation);
	void StopLookMouseCursor();
protected:
};
