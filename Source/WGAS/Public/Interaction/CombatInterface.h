// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"
class UAnimMontage;
// This class does not need to be modified.
UINTERFACE(MinimalAPI,BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WGAS_API ICombatInterface
{
	GENERATED_BODY()

public:

	virtual int32 GetPlayerLevel();
	virtual FVector GetCombatSocketLocation();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void FaceToTarget(const FVector& TargetLocation, float InterpSpeed = 7.5f);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopFaceToTarget();

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void UpdateWarpFacingTarget(const FVector& TargetLocation);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	UAnimMontage* GetHitReactMontage();

	virtual void Die() = 0;
};
