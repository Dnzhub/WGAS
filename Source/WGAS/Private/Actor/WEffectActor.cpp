// Copyright Deniz Yilmaz


#include "Actor/WEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/WAttributeSet.h"
#include "Components/SphereComponent.h"


AWEffectActor::AWEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	SetRootComponent(StaticMeshComponent);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(GetRootComponent());
}


void AWEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWEffectActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AWEffectActor::OnOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AWEffectActor::EndOverlap);
}

void AWEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyState, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Change this to apply a gameplay effect. For now using_const cast but its terrible idea to cast const
	if (IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UWAttributeSet* AttributeSet = Cast<UWAttributeSet>(AbilitySystemInterface->GetAbilitySystemComponent()->GetAttributeSet(UWAttributeSet::StaticClass()));
		UWAttributeSet* MutableAttributeSet = const_cast<UWAttributeSet*>(AttributeSet);
		MutableAttributeSet->SetHealth(AttributeSet->GetHealth() + 25.f);
		MutableAttributeSet->SetMana(AttributeSet->GetMana() - 25.f);

		Destroy();
	}
}

void AWEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
