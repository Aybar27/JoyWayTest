// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "JoyWayGameInstance.generated.h"

class AWeapon;
class AInventoryItem;

UCLASS()
class JOYWAYTEST_API UJoyWayGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		void LoadLevel(FName LevelName, ACharacter* Character);

private:
	UPROPERTY(VisibleAnywhere)
		TArray<TSubclassOf<AWeapon>> Weapons;

	UPROPERTY(VisibleAnywhere)
		TArray<AInventoryItem*> InventoryItems;

	UPROPERTY(EditDefaultsOnly)
		float Health = 100;

	UPROPERTY(VisibleAnywhere)
		bool IsDead = false;

	UPROPERTY()
	bool IsFirstLevel = true;

public:

};
