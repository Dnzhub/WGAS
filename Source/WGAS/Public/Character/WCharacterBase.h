// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WCharacterBase.generated.h"


UCLASS(Abstract)
class WGAS_API AWCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AWCharacterBase();

protected:
	virtual void BeginPlay() override;



};
