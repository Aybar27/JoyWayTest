// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "Components/StaticMeshComponent.h"

ATarget::ATarget()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
}

void ATarget::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &ATarget::OnTakeAnyDamageHandle);
}

void ATarget::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Green, FString(TEXT("Damage to Target")));
}

void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

