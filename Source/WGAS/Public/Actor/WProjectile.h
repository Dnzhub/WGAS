// Copyright Deniz Yilmaz

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class WGAS_API AWProjectile : public AActor
{
	GENERATED_BODY()

public:
	AWProjectile();

	

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	UFUNCTION()
	void OnSphereOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComp;

};
