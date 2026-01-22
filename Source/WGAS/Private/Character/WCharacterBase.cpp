// Copyright Deniz Yilmaz


#include "Character/WCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/WAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "WGAS/WGAS.h"

AWCharacterBase::AWCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile,ECR_Overlap);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(false);

	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), WeaponSocketName);
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AWCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* AWCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void AWCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWCharacterBase::InitAbilityInfo()
{
}


void AWCharacterBase::InitializeDefaultAttributes() const
{
	ApplyGameplayEffect(DefaultPrimaryAttributes);
	ApplyGameplayEffect(DefaultSecondaryAttributes);

	//Vital attributes depends their max values and max values are in secondary attributes
	//Call it after secondary attributes initialized
	ApplyGameplayEffect(DefaultVitalAttributes);

	
	ApplyGameplayEffect(StaminaGenerationGEClass);
	
}

void AWCharacterBase::ConsumeStamina()
{
}

void AWCharacterBase::ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass,float level) const
{
	checkf(IsValid(GetAbilitySystemComponent()), TEXT("AbilitySystemComponent must be valid"));
	checkf(GameplayEffectClass, TEXT("Gameplay effect class is null in AWCharacterBase::ApplyGameplayEffect"));
	
	//Create Context(Whats causing it, who is causing effect, who is target of effect, is fire effect ? frost effect?)
	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this); // What causes this effect ?

	//Create Spec for applying effect
	const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(
		GameplayEffectClass,level,EffectContextHandle);

	//Applying effect to spec is more lightweight than applying effect to self
	
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), GetAbilitySystemComponent());
	

	
}

FVector AWCharacterBase::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

void AWCharacterBase::FaceToTarget_Implementation(const FVector& TargetLocation, float InterpSpeed)
{
	
}

void AWCharacterBase::StopFaceToTarget_Implementation()
{
}

void AWCharacterBase::AddCharacterAbilities()
{
	UWAbilitySystemComponent* ASC = CastChecked<UWAbilitySystemComponent>(AbilitySystemComponent);
	//If not server return
	if (!HasAuthority()) return;
	ASC->AddCharacterAbilities(StartupAbilities);
}


