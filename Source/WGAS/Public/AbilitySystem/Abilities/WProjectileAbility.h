// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "WGameplayAbility.h"
#include "WProjectileAbility.generated.h"

class AWProjectile;
/**
 * 
 */
UCLASS()
class WGAS_API UWProjectileAbility : public UWGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AWProjectile> ProjectileClass;
};
