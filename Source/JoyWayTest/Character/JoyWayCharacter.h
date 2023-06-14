// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JoyWayCharacter.generated.h"

class AWeapon;
class AInventoryItem;
class UJoyWayGameInstance;
struct FWeaponStruct;


UCLASS()
class JOYWAYTEST_API AJoyWayCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AJoyWayCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	void PickUp();
	void Shoot();


private:
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* FollowCamera;

	UPROPERTY()
		AInventoryItem* OverlappingItem;

	UPROPERTY(VisibleAnywhere)
		TArray<AWeapon*> Weapons;

	UPROPERTY(VisibleAnywhere)
		TArray<AInventoryItem*> InventoryItems;

	UPROPERTY(EditDefaultsOnly)
		float Health = 100;

	UPROPERTY(VisibleAnywhere)
		bool IsDead = false;

	UPROPERTY(VisibleAnywhere)
		bool IsFirstLevel = true;

	UPROPERTY(VisibleAnywhere)
		class UHUDInterface* HUDInterface;

	UPROPERTY()
		class AJoyWayGameModeBase* JoyWayGameMode;

	UFUNCTION()
	void OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
		void AttachWeapon(AWeapon* AttachingWeapon, int32 WeaponIndex);
	
public:
	UFUNCTION()
	void SetOverlappingWeapon(AInventoryItem* InventoryItem);
	
	UFUNCTION()
	void ChangeLevel();

	UFUNCTION()
	void Init(TArray<TSubclassOf<AWeapon>> WeaponsInit, TArray<AInventoryItem*> InventoryItemsInit, float HealthInit = 100, bool IsDeadInit = false, bool IsFirstLevelInit = true);
	
	UFUNCTION()
		void PrintSMTH();

	UFUNCTION()
		TArray<AWeapon*> GetWeapons();

	UFUNCTION()
		TArray<AInventoryItem*> GetInventoryItems();

	UFUNCTION()
		float GetHealth();

	UFUNCTION()
		bool GetIsDead();

	UFUNCTION()
		bool GetIsFirstLevel();
};
