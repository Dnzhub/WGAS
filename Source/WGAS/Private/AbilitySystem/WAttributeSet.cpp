// Copyright Deniz Yilmaz


#include "AbilitySystem/WAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UWAttributeSet::UWAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(25.f);
	InitMaxMana(100.f);
	InitStamina(100.f);
	InitMaxStamina(100.f);
}


//Register for Replication boilerplate
void UWAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/**
	*REPNOTIFY_Always  even if the new value and old value are both the same, the function will run.

	with REPNOTIFY_OnChangged, it will only run if the newvalue and oldvalue are different
	 * **/
	DOREPLIFETIME_CONDITION_NOTIFY(UWAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWAttributeSet,Stamina,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWAttributeSet,MaxStamina,COND_None,REPNOTIFY_Always);

	
}

void UWAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	
	}
	
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());

	}
	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxStamina());
	}

}

void UWAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	
}

void UWAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data,
	FEffectProperties& EffectProperties) const
{
		
	//Source : Causer of the effect
	//Target : target of the effect(owner of this Attribute set)

	EffectProperties.EffectContextHandle = Data.EffectSpec.GetContext();
	EffectProperties.SourceASC = EffectProperties.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(EffectProperties.SourceASC) && EffectProperties.SourceASC->AbilityActorInfo.IsValid() &&
		EffectProperties.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		//Get causer actor
		EffectProperties.SourceAvatarActor = EffectProperties.SourceASC->AbilityActorInfo->AvatarActor.Get();
		//Get causer controller
		EffectProperties.SourceController = EffectProperties.SourceASC->AbilityActorInfo->PlayerController.Get();
		//If controller null try to get it from pawn
		if (!EffectProperties.SourceController && EffectProperties.SourceAvatarActor)
		{
			if (const APawn* SourcePawn = Cast<APawn>(EffectProperties.SourceAvatarActor))
			{
				EffectProperties.SourceController = SourcePawn->GetController();
			}
		}
		//Get causer character
		if (EffectProperties.SourceController)
		{
			EffectProperties.SourceCharacter = Cast<ACharacter>(EffectProperties.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		//Get target actor
		EffectProperties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		//Get target controller
		EffectProperties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		//Get target character
		EffectProperties.TargetCharacter = Cast<ACharacter>(EffectProperties.TargetAvatarActor);
		//Get target ability system comp
		EffectProperties.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectProperties.TargetAvatarActor);
	}
	
}


//Called right after health attribute replicated
void UWAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWAttributeSet,Health, OldHealth);
}

void UWAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWAttributeSet,MaxHealth, OldMaxHealth);

}

void UWAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWAttributeSet,Mana, OldMana);
}

void UWAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWAttributeSet,MaxMana, OldMaxMana);

}

void UWAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWAttributeSet,MaxMana, OldStamina);

}

void UWAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWAttributeSet,MaxMana, OldMaxStamina);

}

