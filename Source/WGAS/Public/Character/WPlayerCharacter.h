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
	// Sets default values for this character's properties
	AWPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
