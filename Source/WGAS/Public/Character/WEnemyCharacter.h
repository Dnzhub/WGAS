// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "WCharacterBase.h"
#include "Interaction/Interactable.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "WEnemyCharacter.generated.h"

struct FGameplayTag;
struct FWidgetControllerParams;
class UEnemyWidgetController;
class UWUserWidget;
class UWidgetComponent;

UCLASS()
class WGAS_API AWEnemyCharacter : public AWCharacterBase, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWEnemyCharacter();

	/** IInteractable **/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** End IInteractable **/

	/** Combat Interface **/
	virtual int32 GetPlayerLevel() override;
	/** End Combat Interface **/

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category= "Combat")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadOnly, Category= "Combat")
	float BaseWalkSpeed = 250.f;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityInfo() override;
	virtual void InitializeDefaultAttributes() const override;


	UEnemyWidgetController* GetEnemyWidgetController(const FWidgetControllerParams& WCParams);

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UEnemyWidgetController> EnemyWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UEnemyWidgetController> EnemyWidgetController;
	
	void InitHealthBarWidget(ACharacter* CH,UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

};
