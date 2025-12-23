// Copyright Deniz Yilmaz


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"
#include "WGAS/WGAS.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
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
		AddUObject(this, &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);

		//Has delegate already been set and if we should still listen for it ?
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		if (!bCalledDelegate)
		{
			//Tell the server we are still waiting for remote player data
			SetWaitingOnRemotePlayerData();
		}
	}

	
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	if (APlayerController* Controller = Ability->GetCurrentActorInfo()->PlayerController.Get())
	{
		//FScopedPredictionWindow : Everything in this scope should be predicted
		FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
		
		ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(ECC_Cursor);

		FHitResult Hit;
		bool bHit = Controller->GetHitResultUnderCursorByChannel(TraceType,false,Hit);

		FGameplayAbilityTargetDataHandle DataHandle;
		FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
		Data->HitResult = Hit;
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
			ValidData.Broadcast(DataHandle);
		}
	}
	
	
}

//Called on server when replicated data received
void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag ActivationTag)
{
	//Tells to ability system target data has been received dont keep it stored
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());

	//check ability currently active so we can broadcast it
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
