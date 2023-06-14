// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageActor.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ADamageActor::ADamageActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetActorTickInterval(1.f);

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}

void ADamageActor::BeginPlay()
{
	Super::BeginPlay();

}

void ADamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 12, SphereColor, false, 1.1f, (uint8)0U, 2.f);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, nullptr, {}, this, nullptr, true);
}

void ADamageActor::ApplyDamage()
{

}



