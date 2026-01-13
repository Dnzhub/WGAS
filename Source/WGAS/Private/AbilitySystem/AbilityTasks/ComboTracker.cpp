// Copyright Deniz Yilmaz


#include "AbilitySystem/AbilityTasks/ComboTracker.h"

#include "AbilitySystemComponent.h"

UComboTracker* UComboTracker::CreateCombatTracker(UGameplayAbility* OwningAbility, int ComboIndex,
	float TimeSinceLastUsed)
{
	UComboTracker* MyObj = NewAbilityTask<UComboTracker>(OwningAbility);
	MyObj->ComboIndex = ComboIndex;
	MyObj->TimeSinceLastUsed = TimeSinceLastUsed;
	return MyObj;
}

void UComboTracker::Activate()
{
	if (IsLocallyControlled())
	{
		SendMouseCursorData();
	}
	else
	{
		//We are on the server, listen for target data

		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();

		//Target data received from server, call the callback
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).
		AddUObject(this, &UComboTracker::OnTargetDataReplicatedCallback);

		//Has delegate already been set and if we should still listen for it ?
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		if (!bCalledDelegate)
		{
			//Tell the server we are still waiting for remote player data
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UComboTracker::SendMouseCursorData()
{
	if (APlayerController* Controller = Ability->GetCurrentActorInfo()->PlayerController.Get())
	{
		//FScopedPredictionWindow : Everything in this scope should be predicted
		FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
		

		FGameplayAbilityTargetDataHandle DataHandle;
		FGameplayAbilityTargetData_ComboData* Data = new FGameplayAbilityTargetData_ComboData();
		Data->ComboIndex = ComboIndex;
		Data->TimeSinceLastUsed = TimeSinceLastUsed;
		DataHandle.Add(Data);
		
		

		//Send target data to server
		AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(),
			GetActivationPredictionKey(),
			DataHandle,
			FGameplayTag(),
			AbilitySystemComponent->ScopedPredictionKey);

		//check ability currently active so we can broadcast it
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			//To see hit data  on the local client 
			ValidData.Broadcast(ComboIndex,TimeSinceLastUsed);
		}
	}
}

//Called on server when replicated data received
void UComboTracker::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag ActivationTag)
{
	//Tells to ability system target data has been received dont keep it stored
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());

	//check ability currently active so we can broadcast it
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(ComboIndex,TimeSinceLastUsed);
	}
}
