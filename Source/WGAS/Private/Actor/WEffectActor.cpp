// Copyright Deniz Yilmaz


#include "Actor/WEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/WAbilitySystemComponent.h"


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

void AWEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantGameplayEffectPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationGameplayEffectPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if (InfiniteGameplayEffectPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
}

void AWEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantGameplayEffectPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}
	if (DurationGameplayEffectPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if (InfiniteGameplayEffectPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}

	//Remove infinite effect
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (const TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*>& HandlePair : ActiveEffectHandles)
		{
			if (TargetASC ==  HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key,1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}
		for (const FActiveGameplayEffectHandle& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
	
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
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetAbilitySystemComp->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

						     //Get gameplay effect itself
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;

	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle,TargetAbilitySystemComp);
	}
	
}


