// Copyright Deniz Yilmaz


#include "WAssetManager.h"
#include "WGameplayTags.h"

UWAssetManager& UWAssetManager::Get()
{
	check(GEngine);

	UWAssetManager* AssetManager = Cast<UWAssetManager>(GEngine->AssetManager);
	return *AssetManager;
}

void UWAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FWGameplayTags::InitializeNativeGameplayTags();
}
