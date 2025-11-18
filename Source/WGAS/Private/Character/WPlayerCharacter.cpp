// Copyright Deniz Yilmaz


#include "Character/WPlayerCharacter.h"


// Sets default values
AWPlayerCharacter::AWPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

