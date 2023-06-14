// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageActor.generated.h"

UCLASS()
class JOYWAYTEST_API ADamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADamageActor();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly)
	float Radius = 200;

	UPROPERTY(EditDefaultsOnly)
	FColor SphereColor = FColor::Red;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 49;

private:
	UFUNCTION()
	void ApplyDamage();

public:	


};
