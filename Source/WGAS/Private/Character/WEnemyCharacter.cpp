// Copyright Deniz Yilmaz


#include "Character/WEnemyCharacter.h"

#include "AbilitySystem/WAbilitySystemComponent.h"
#include "AbilitySystem/WAbilitySystemLibrary.h"
#include "AbilitySystem/WAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/WUserWidget.h"
#include "UI/WidgetController/EnemyWidgetController.h"
#include "WGAS/WGAS.h"


AWEnemyCharacter::AWEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UWAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UWAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	HealthBar->SetupAttachment(GetRootComponent());

}

void AWEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityInfo();

	InitHealthBarWidget(this,AbilitySystemComponent,AttributeSet);

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

int32 AWEnemyCharacter::GetPlayerLevel()
{
	return Level;
}


void AWEnemyCharacter::InitAbilityInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	Cast<UWAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}

void AWEnemyCharacter::InitializeDefaultAttributes() const
{
	UWAbilitySystemLibrary::InitializeDefaultAttributes(this,CharacterClass, Level,AbilitySystemComponent);
	
}

UEnemyWidgetController* AWEnemyCharacter::GetEnemyWidgetController(const FWidgetControllerParams& WCParams)
{
	if (!EnemyWidgetController)
	{
		EnemyWidgetController = NewObject<UEnemyWidgetController>(this,EnemyWidgetControllerClass);
		EnemyWidgetController->SetWidgetControllerParams(WCParams);
		EnemyWidgetController->BindCallbackDependencies();
	}
	return EnemyWidgetController;
}

void AWEnemyCharacter::InitHealthBarWidget(ACharacter* CH, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(HealthBarWidgetClass, TEXT("HealthBar Widget Class is NULL, fill out EnemyCharacter class"));
	checkf(EnemyWidgetControllerClass, TEXT("Enemy Widget Controller Class is NULL, fill EnemyCharacter class"));

	HealthBar->SetWidgetClass(HealthBarWidgetClass);
	HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBar->SetDrawAtDesiredSize(true);
	
	const FWidgetControllerParams WidgetControllerParams(ASC,AS,CH);
	UEnemyWidgetController* WidgetController =  GetEnemyWidgetController(WidgetControllerParams); //Construct  widget controller
	UWUserWidget* Widget = Cast<UWUserWidget>(HealthBar->GetWidget());

	checkf(Widget, TEXT("Widget cast failed in EnemyCharacter"));
	
	Widget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	
	
}

