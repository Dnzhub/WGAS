// Copyright Deniz Yilmaz


#include "Character/WEnemyCharacter.h"

#include "Components/CapsuleComponent.h"
#include "WGAS/WGAS.h"


AWEnemyCharacter::AWEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
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

