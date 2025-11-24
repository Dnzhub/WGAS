// Copyright Deniz Yilmaz


#include "Controller/WPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/WPlayerCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AWPlayerController::AWPlayerController()
{
	//If any change on server stream it to all clients with replication
	bReplicates = true;
}

bool AWPlayerController::IsAiming()
{
	return bIsAiming;
}

void AWPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(PlayerContext);

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(SubSystem);

	SubSystem->AddMappingContext(PlayerContext,0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

}

void AWPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AWPlayerController::Move);
	EnhancedInputComponent->BindAction(AimAction,ETriggerEvent::Triggered,this,&AWPlayerController::LookMouseCursor);
	EnhancedInputComponent->BindAction(AimAction,ETriggerEvent::Completed,this,&AWPlayerController::StopLookMouseCursor);

}

void AWPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ControlledCharacter = Cast<AWPlayerCharacter>(InPawn);
}

void AWPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2d InputAxisVector  = Value.Get<FVector2D>();
	if (ControlledCharacter)
	{
		ControlledCharacter->Move(InputAxisVector);
	}
}
bool AWPlayerController::GetLookLocation(FVector& OutLocation) const
{
	FHitResult HitResult;
	ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECC_Cursor);

	bool bHit = GetHitResultUnderCursorByChannel(TraceType,true,HitResult);
	if (bHit)
	{
		OutLocation = HitResult.Location;
	}
	return bHit;
}

void AWPlayerController::LookMouseCursor() 
{
	bIsAiming = true;
	FVector LookLocation;
	if (GetLookLocation(LookLocation))
	{
		check(ControlledCharacter);
		ControlledCharacter->LookMouseCursor(LookLocation);
	}
	

}

void AWPlayerController::StopLookMouseCursor()
{
	bIsAiming = false;
	check(ControlledCharacter);
	ControlledCharacter->StopLookMouseCursor();
}

