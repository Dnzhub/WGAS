// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "WAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class WGAS_API UWAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UWAssetManager& Get();

protected:
	//Initial loading for assets
	virtual void StartInitialLoading() override;
};
