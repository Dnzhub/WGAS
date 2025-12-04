// Copyright Deniz Yilmaz


#include "Character/WCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"

AWCharacterBase::AWCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AWCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AWCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWCharacterBase::ApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	if (!AbilitySystemComponent) return;

	checkf(GameplayEffectClass, TEXT("Gameplay effect class is null in AWCharacterBase::ApplyGameplayEffect"));
	
	//Create Context(Whats causing it, who is causing effect, who is target of effect, is fire effect ? frost effect?)
	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this); // What causes this effect ?

	//Create Spec for applying effect
	const FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
		GameplayEffectClass,1.f,EffectContextHandle);

	//Applying effect to spec is more lightweight than applying effect to self
	const FActiveGameplayEffectHandle ActiveEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	
}


