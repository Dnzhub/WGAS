// Copyright Deniz Yilmaz


#include "State/WPlayerState.h"

#include "AbilitySystem/WAbilitySystemComponent.h"
#include "AbilitySystem/WAttributeSet.h"

AWPlayerState::AWPlayerState()
{
	

	AbilitySystemComponent = CreateDefaultSubobject<UWAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UWAttributeSet>("AttributeSet");

	//How often server update the clients
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AWPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
