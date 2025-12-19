// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class WGAS_API UWGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;
};
