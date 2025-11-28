// Copyright Deniz Yilmaz


#include "Actor/WEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


AWEffectActor::AWEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
}


void AWEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWEffectActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AWEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetAbilitySystemComp = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetAbilitySystemComp) return;

	check(GameplayEffectClass);
	
	//Create Context(Whats causing it, who is causing effect, who is target of effect, is fire effect ? frost effect?)
	FGameplayEffectContextHandle EffectContextHandle = TargetAbilitySystemComp->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this); // What causes this effect ?

	//Create Spec for applying effect
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComp->MakeOutgoingSpec(
		GameplayEffectClass,1.f,EffectContextHandle);

	//Applying effect to spec is more lightweight than applying effect to self
	TargetAbilitySystemComp->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}


