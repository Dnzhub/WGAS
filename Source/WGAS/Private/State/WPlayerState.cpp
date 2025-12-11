// Copyright Deniz Yilmaz


#include "State/WPlayerState.h"

#include "AbilitySystem/WAbilitySystemComponent.h"
#include "AbilitySystem/WAttributeSet.h"
#include "Net/UnrealNetwork.h"

AWPlayerState::AWPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UWAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UWAttributeSet>("AttributeSet");

	//How often server update the clients
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AWPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AWPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AWPlayerState,level)
}

void AWPlayerState::OnRep_Level(int32 OldLevel)
{
	
}
