// Copyright Deniz Yilmaz


#include "AbilitySystem/WAbilitySystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "State/WPlayerState.h"
#include "UI/HUD/WHUD.h"
#include "UI/WidgetController/WWidgetController.h"

UWOverlayWidgetController* UWAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AWHUD* WHUD = Cast<AWHUD>(PC->GetHUD()))
		{
			AWPlayerState* PS = PC->GetPlayerState<AWPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			ACharacter* CH = PC->GetCharacter();
			const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS,CH);
			
			return WHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UWAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AWHUD* WHUD = Cast<AWHUD>(PC->GetHUD()))
		{
			AWPlayerState* PS = PC->GetPlayerState<AWPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			ACharacter* CH = PC->GetCharacter();
			const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS,CH);
			
			return WHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
