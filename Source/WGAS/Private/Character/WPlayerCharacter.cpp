// Copyright Deniz Yilmaz


#include "Character/WPlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


AWPlayerCharacter::AWPlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 400.f, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AWPlayerCharacter::Move(const FVector2d& MovementVector)
{
	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(ForwardDir,MovementVector.Y);
	AddMovementInput(RightDir,MovementVector.X);
}

void AWPlayerCharacter::LookMouseCursor(const FVector& TargetLocation)
//Target location comes from GetHitResultUnderCursorByChannel in player controller -> GetLookLocation()
{
		
	GetCharacterMovement()->bOrientRotationToMovement = false;

	FVector StartLocation = FVector(GetActorLocation().X,GetActorLocation().Y,TargetLocation.Z);
	
	float DeltaSecond = UGameplayStatics::GetWorldDeltaSeconds(this);

	FRotator TargetRot = FMath::RInterpTo(GetActorRotation(),
		UKismetMathLibrary::FindLookAtRotation(StartLocation,TargetLocation),
		DeltaSecond,7.5);

	SetActorRotation(TargetRot);
	
}

void AWPlayerCharacter::StopLookMouseCursor()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

