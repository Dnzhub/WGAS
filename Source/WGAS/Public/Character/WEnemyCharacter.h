// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "WCharacterBase.h"
#include "Interaction/Interactable.h"
#include "WEnemyCharacter.generated.h"

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
protected:
	virtual void BeginPlay() override;
};
