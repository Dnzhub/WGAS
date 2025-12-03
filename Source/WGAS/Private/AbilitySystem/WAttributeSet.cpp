// Copyright Deniz Yilmaz


#include "AbilitySystem/WAttributeSet.h"

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

