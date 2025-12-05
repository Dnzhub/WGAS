// Copyright Deniz Yilmaz


#include "Character/WEnemyCharacter.h"

#include "AbilitySystem/WAbilitySystemComponent.h"
#include "AbilitySystem/WAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "WGAS/WGAS.h"


AWEnemyCharacter::AWEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UWAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UWAttributeSet>("AttributeSet");
}

void AWEnemyCharacter::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AWEnemyCharacter::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AWEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityInfo();
}

void AWEnemyCharacter::InitAbilityInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	Cast<UWAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

}

