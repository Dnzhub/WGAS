// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "ComboTracker.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FComboTrackerDataSignature, int, ComboIndex, float, TimeSinceLastUsed);

USTRUCT()
struct FGameplayAbilityTargetData_ComboData : public FGameplayAbilityTargetData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int ComboIndex;

	UPROPERTY()
	float TimeSinceLastUsed;

	// Required overrides
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGameplayAbilityTargetData_ComboData::StaticStruct();
	}

	
	// how to pack and unpack your data when sending it over the network
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
	{
		Ar << ComboIndex;
		Ar << TimeSinceLastUsed;
		bOutSuccess = true;
		return true;
	}
};

template<>
struct TStructOpsTypeTraits<FGameplayAbilityTargetData_ComboData> : public TStructOpsTypeTraitsBase2<FGameplayAbilityTargetData_ComboData>
{
	enum
	{
		WithNetSerializer = true
	};
};

UCLASS()
class WGAS_API UComboTracker : public UAbilityTask
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "CombatTracker", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UComboTracker* CreateCombatTracker(UGameplayAbility* OwningAbility, int ComboIndex, float TimeSinceLastUsed);

	UPROPERTY(BlueprintAssignable)
	FComboTrackerDataSignature ValidData;

private:

	virtual void Activate() override;

	void SendMouseCursorData();

	//Called on server when replicated data received
	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);

	int ComboIndex{0};
	float TimeSinceLastUsed{-999.f};
};
