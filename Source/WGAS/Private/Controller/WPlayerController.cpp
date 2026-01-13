// Copyright Deniz Yilmaz


#include "Controller/WPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"
#include "WGameplayTags.h"
#include "AbilitySystem/WAbilitySystemComponent.h"
#include "Character/WPlayerCharacter.h"
#include "Input/WInputComponent.h"
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

	UWInputComponent* WInputComponent = CastChecked<UWInputComponent>(InputComponent);
	WInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AWPlayerController::Move);
	WInputComponent->BindAction(AimAction,ETriggerEvent::Triggered,this,&AWPlayerController::LookMouseCursor);
	WInputComponent->BindAction(AimAction,ETriggerEvent::Completed,this,&AWPlayerController::StopLookMouseCursor);
	WInputComponent->BindAction(DashAction,ETriggerEvent::Started,this,&AWPlayerController::Dash);
	WInputComponent->BindAction(AttributeMenuAction,ETriggerEvent::Started,this,&AWPlayerController::AttributeMenuPressed);

	WInputComponent->BindAbilityActions(InputConfig,this,&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagReleased,&ThisClass::AbilityInputTagHeld);
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
	ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECC_Cursor);

	FHitResult Hit;
	bool bHit = GetHitResultUnderCursorByChannel(TraceType,true,Hit);
	 if (bHit)
	 {
	 	if(ControlledCharacter)
	 	{
	 		ControlledCharacter->Execute_FaceToTarget(ControlledCharacter,Hit.Location,7.5f);
	 	}
	 }
	
	
}

void AWPlayerController::StopLookMouseCursor()
{
	if(ControlledCharacter)
	{
		ControlledCharacter->Execute_StopFaceToTarget(ControlledCharacter);
	}
}

void AWPlayerController::CursorTrace()
{
	
	GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
	if (!HitResult.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = HitResult.GetActor();

	if (LastActor != ThisActor)
	{
		if (LastActor) LastActor->UnHighlightActor();
		if (ThisActor) ThisActor->HighlightActor();
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

void AWPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//if input is LMB
	if (!GetAbilitySystemComponent()) return;
	if (InputTag.MatchesTagExact(FWGameplayTags::Get().InputTag_RMB) )
	{
		GetAbilitySystemComponent()->AddLooseGameplayTag(InputTag);
	}

}

void AWPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!GetAbilitySystemComponent()) return;

	GetAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
	if (InputTag.MatchesTagExact(FWGameplayTags::Get().InputTag_RMB) )
	{
		GetAbilitySystemComponent()->RemoveLooseGameplayTag(InputTag);
	}
}

void AWPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!GetAbilitySystemComponent()) return;;
	
	GetAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
}

UWAbilitySystemComponent* AWPlayerController::GetAbilitySystemComponent()
{
	if (!WAbilitySystemComponent)
	{
		WAbilitySystemComponent = Cast<UWAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(
			GetPawn<APawn>()));
	}
	return WAbilitySystemComponent;
}