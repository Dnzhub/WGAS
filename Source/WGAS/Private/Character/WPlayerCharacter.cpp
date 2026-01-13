// Copyright Deniz Yilmaz


#include "Character/WPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Controller/WPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "State/WPlayerState.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystem/WAbilitySystemComponent.h"
#include "AbilitySystem/WAttributeSet.h"
#include "UI/HUD/WHUD.h"


AWPlayerCharacter::AWPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;


	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 400.f, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	bIsDashing = false;
	DashCooldown = 1.5;
	DashSpeed = 8000.f;
}
void AWPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//Set ability system component owner and avatar for the server
	InitAbilityInfo();
	AddCharacterAbilities();
}

void AWPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//Set ability system component owner and avatar for the client
	InitAbilityInfo();
}

int32 AWPlayerCharacter::GetPlayerLevel()
{
	const AWPlayerState* PS = GetPlayerState<AWPlayerState>();
	check(PS);
	return PS->GetPlayerLevel();
}

void AWPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
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

void AWPlayerCharacter::FaceToTarget_Implementation(const FVector& TargetLocation,float InterpSpeed)
//Target location comes from GetHitResultUnderCursorByChannel in player controller -> GetLookLocation()
{
	bIsAiming = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	FVector StartLocation = FVector(GetActorLocation().X,GetActorLocation().Y,TargetLocation.Z);
	
	float DeltaSecond = UGameplayStatics::GetWorldDeltaSeconds(this);

	FRotator TargetRot = FMath::RInterpTo(GetActorRotation(),
		UKismetMathLibrary::FindLookAtRotation(StartLocation,TargetLocation),
		DeltaSecond,InterpSpeed);

	SetActorRotation(TargetRot);
	
}

void AWPlayerCharacter::StopFaceToTarget_Implementation()
{
	bIsAiming = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AWPlayerCharacter::Dash()
{
	if (UWAttributeSet* Attribute = CastChecked<UWAttributeSet>(AttributeSet))
	{
		if (Attribute->GetStamina() < StaminaCost) return;
	}
	if (bIsDashing || GetCharacterMovement()->IsFalling()) return;
	
	bIsDashing = true;
	PlayDashEffect();
	ConsumeStamina();

	GetCharacterMovement()->FallingLateralFriction = 5.f;
	FVector Direction;
	if (GetLastMovementInputVector().IsNearlyZero())
	{
		Direction = GetActorForwardVector(); // idle
	}
	else
	{
		Direction = GetLastMovementInputVector().GetSafeNormal(); // Move
	}
	FVector Velocity = Direction * DashSpeed;
	Velocity.Z = 0.f;
	
	LaunchCharacter(Velocity,true,true);
	
	FTimerHandle DashTimerHandle;
	GetWorldTimerManager().SetTimer(DashTimerHandle,[this]()
	{
		bIsDashing = false;
		GetCharacterMovement()->FallingLateralFriction = 0.f;

	},DashCooldown,false);


}

void AWPlayerCharacter::ConsumeStamina()
{
	ApplyGameplayEffect(StaminaConsumptionGEClass);
	OnStaminaConsume.Broadcast();
}


void AWPlayerCharacter::PlayDashEffect()
{
	UNiagaraComponent* EffectComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
	DashEffect,
	GetRootComponent(),
	NAME_None,
	FVector::ZeroVector,
	FRotator::ZeroRotator,
	EAttachLocation::Type::KeepRelativeOffset,
	true
	);
	

}




void AWPlayerCharacter::InitAbilityInfo()
{
	AWPlayerState* PS = GetPlayerState<AWPlayerState>();
	check(PS);
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	Cast<UWAbilitySystemComponent>(PS->GetAbilitySystemComponent())->AbilityActorInfoSet();
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
			MyHUD->InitOverlay(PlayerController,this,PS,AbilitySystemComponent,AttributeSet);
		}
	}
	InitializeDefaultAttributes();
	
}


