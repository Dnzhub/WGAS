// Copyright Deniz Yilmaz


#include "Character/WPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Controller/WPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "State/WPlayerState.h"
#include "UI/HUD/WHUD.h"


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



void AWPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//Set ability system component owner and avatar for the server
	InitAbilityInfo();
}

void AWPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//Set ability system component owner and avatar for the client
	InitAbilityInfo();
}
void AWPlayerCharacter::InitAbilityInfo()
{
	AWPlayerState* PS = GetPlayerState<AWPlayerState>();
	check(PS);
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	
	AbilitySystemComponent = PS->GetAbilitySystemComponent();
	AttributeSet = PS->GetAttributeSet();

	/**
	//Only client itself has valid player controller. 
	//EG. if 3 players are playing, Your machine only has valid player controller. Other 2  character copies has no valid player controller
	//So we need to check controller if it valid
	 * **/
	if (AWPlayerController* PlayerController = Cast<AWPlayerController>(GetController()))
	{
		if (AWHUD* MyHUD = Cast<AWHUD>(PlayerController->GetHUD()))
		{
			MyHUD->InitOverlay(PlayerController,PS,AbilitySystemComponent,AttributeSet);
		}
	}
	
	
}

