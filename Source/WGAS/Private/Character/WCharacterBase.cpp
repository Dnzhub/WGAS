// Copyright Deniz Yilmaz


#include "Character/WCharacterBase.h"

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


