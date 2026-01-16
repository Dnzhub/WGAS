// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "WGameplayAbility.h"
#include "WProjectileAbility.generated.h"

class AWProjectile;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class WGAS_API UWProjectileAbility : public UWGameplayAbility
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AWProjectile> ProjectileClass;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
};
