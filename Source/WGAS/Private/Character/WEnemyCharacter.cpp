// Copyright Deniz Yilmaz


#include "Character/WEnemyCharacter.h"


// Sets default values
AWEnemyCharacter::AWEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

