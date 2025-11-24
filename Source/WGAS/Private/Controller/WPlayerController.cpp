// Copyright Deniz Yilmaz


#include "Controller/WPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
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

void AWPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2d InputAxisVector  = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDir,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDir,InputAxisVector.X);
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
		ACharacter* ControlledPawn = GetPawn<ACharacter>();
		check(ControlledPawn);
		ControlledPawn->GetCharacterMovement()->bOrientRotationToMovement = false;

		FVector StartLocation = FVector(ControlledPawn->GetActorLocation().X,ControlledPawn->GetActorLocation().Y,LookLocation.Z);
		
		float DeltaSecond = UGameplayStatics::GetWorldDeltaSeconds(this);

		FRotator TargetRot = FMath::RInterpTo(ControlledPawn->GetActorRotation(),
			UKismetMathLibrary::FindLookAtRotation(StartLocation,LookLocation),
			DeltaSecond,7.5);

		ControlledPawn->SetActorRotation(TargetRot);
	}
	

}

void AWPlayerController::StopLookMouseCursor()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "StopLookMouseCursor");
	bIsAiming = false;
	ACharacter* ControlledCharacter = GetPawn<ACharacter>();
	check(ControlledCharacter);
	ControlledCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}

