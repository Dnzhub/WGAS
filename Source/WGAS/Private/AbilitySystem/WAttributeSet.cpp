// Copyright Deniz Yilmaz


#include "AbilitySystem/WAttributeSet.h"

#include "Net/UnrealNetwork.h"

UWAttributeSet::UWAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitMana(250.f);
	InitMaxMana(250.f);
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