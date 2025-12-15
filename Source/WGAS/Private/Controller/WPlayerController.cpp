// Copyright Deniz Yilmaz


#include "Controller/WPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/WPlayerCharacter.h"
#include "Interaction/Interactable.h"
#include "WGAS/WGAS.h"

AWPlayerController::AWPlayerController()
{
	//If any change on server stream it to all clients with replication
	bReplicates = true;
}



void AWPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(PlayerContext);

	if (IsLocalController())
	{
	
		if(UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(PlayerContext,0);
		}
		
		bShowMouseCursor = true;
		DefaultMouseCursor = EMouseCursor::Default;

		FInputModeGameAndUI InputModeData;
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputModeData.SetHideCursorDuringCapture(false);
		SetInputMode(InputModeData);
	}

}
void AWPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CursorTrace();
	
}

void AWPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AWPlayerController::Move);
	EnhancedInputComponent->BindAction(AimAction,ETriggerEvent::Triggered,this,&AWPlayerController::LookMouseCursor);
	EnhancedInputComponent->BindAction(AimAction,ETriggerEvent::Completed,this,&AWPlayerController::StopLookMouseCursor);
	EnhancedInputComponent->BindAction(DashAction,ETriggerEvent::Started,this,&AWPlayerController::Dash);
	EnhancedInputComponent->BindAction(AttributeMenuAction,ETriggerEvent::Started,this,&AWPlayerController::AttributeMenuPressed);

}

void AWPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ControlledCharacter = Cast<AWPlayerCharacter>(InPawn);
}
void AWPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();
	ControlledCharacter = Cast<AWPlayerCharacter>(GetPawn());

}
bool AWPlayerController::IsAiming()
{
	return bIsAiming;
}

void AWPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2d InputAxisVector  = Value.Get<FVector2D>();
	if (ControlledCharacter)
	{
		ControlledCharacter->Move(InputAxisVector);
	}
}


void AWPlayerController::LookMouseCursor() 
{
	bIsAiming = true;
	FHitResult HitResult;
	ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECC_Cursor);

	bool bHit = GetHitResultUnderCursorByChannel(TraceType,true,HitResult);
	if (bHit)
	{
		if(ControlledCharacter)
		{
			ControlledCharacter->LookMouseCursor( HitResult.Location);
		}
	}

	
}

void AWPlayerController::StopLookMouseCursor()
{
	bIsAiming = false;
	if(ControlledCharacter)
	{
		ControlledCharacter->StopLookMouseCursor();
	}
}

void AWPlayerController::CursorTrace()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
	if (!HitResult.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = HitResult.GetActor();

	if (!LastActor)
	{
		if (ThisActor)
		{
			ThisActor->HighlightActor();
		}
	}
	else //LastActor is valid
	{
		if (!ThisActor)
		{
			LastActor->UnHighlightActor();
		}
		else // Both actors are valid
		{
			if (LastActor != ThisActor)
			{
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
		}
	}
}

void AWPlayerController::Dash()
{
	if (ControlledCharacter)
	{
		ControlledCharacter->Dash();
	}
}

void AWPlayerController::AttributeMenuPressed()
{
	OnAttributeMenuPressed.Broadcast();
}

