// Copyright Deniz Yilmaz


#include "Actor/WProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


AWProjectile::AWProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SetRootComponent(SphereComp);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);

	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Overlap);
	SphereComp->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Overlap);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = 550.f;
	ProjectileMovementComponent->MaxSpeed = 550.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

}

void AWProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AWProjectile::OnSphereOverlap);
	
}

void AWProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}


