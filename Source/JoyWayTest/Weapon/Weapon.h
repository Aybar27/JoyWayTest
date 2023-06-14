// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JoyWayTest/InventoryItem/InventoryItem.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_Initial UMETA(DisplayName = "InitialState"),
	EWS_Equipped UMETA(DisplayName = "Equipped"),
	EWS_NotEquipped UMETA(DisplayName = "NotEquipped"),

	EWS_Max UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class JOYWAYTEST_API AWeapon : public AInventoryItem
{
	GENERATED_BODY()
	
public:

protected:
	UPROPERTY(EditAnywhere)
	float TraceMaxDistance = 1500.f;

	UPROPERTY(EditAnywhere)
		int32 AMMO;

private:


public:
	UPROPERTY(VisibleAnywhere)
		EWeaponState WeaponState;

	UFUNCTION(BlueprintCallable)
		bool Shoot();

	UFUNCTION(BlueprintCallable)
		int32 GetAMMO();

	

};

