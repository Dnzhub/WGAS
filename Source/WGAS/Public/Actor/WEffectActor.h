// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WEffectActor.generated.h"

class USphereComponent;

UCLASS()
class WGAS_API AWEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AWEffectActor();

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyState, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
};
