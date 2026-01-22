// Copyright Deniz Yilmaz


#include "AbilitySystem/WAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "Game/WGameModeBase.h"
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

void UWAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject,ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* AbilitySystemComponent)
{
	AWGameModeBase* GameMode = Cast<AWGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!GameMode) return;

	AActor* AvatarActor = AbilitySystemComponent->GetAvatarActor();

	UCharacterClassInfo* CharacterClassInfo = GameMode->CharacterClassInfo;
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributesContextHandle =  AbilitySystemComponent->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level,PrimaryAttributesContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());


	FGameplayEffectContextHandle SecondaryAttributesContextHandle =  AbilitySystemComponent->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());


	FGameplayEffectContextHandle VitalAttributesContextHandle =  AbilitySystemComponent->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

void UWAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject,
	UAbilitySystemComponent* AbilitySystemComponent)
{
	AWGameModeBase* GameMode = Cast<AWGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!GameMode) return;

	UCharacterClassInfo* CharacterClassInfo = GameMode->CharacterClassInfo;
	for (const TSubclassOf<UGameplayAbility>& AbilityClass : CharacterClassInfo->SharedAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
		AbilitySystemComponent->GiveAbility(AbilitySpec);

	}
} 
