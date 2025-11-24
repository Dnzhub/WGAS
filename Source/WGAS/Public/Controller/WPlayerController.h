// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WPlayerController.generated.h"

/**
 * 
 */
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


#define ECC_Cursor ECC_GameTraceChannel1

UCLASS()
class WGAS_API AWPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AWPlayerController();

	UFUNCTION(BlueprintCallable, Category = Input)
	bool IsAiming();


protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	UPROPERTY(BlueprintReadWrite, Category = Input)
	bool bIsAiming;

private:
	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> PlayerContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> AimAction;

	void Move(const FInputActionValue& Value);

	bool GetLookLocation(FVector& OutLocation) const;

	void LookMouseCursor();
	void StopLookMouseCursor();

	
};

