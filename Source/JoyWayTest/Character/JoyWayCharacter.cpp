// Fill out your copyright notice in the Description page of Project Settings.


#include "JoyWayCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JoyWayTest/InventoryItem/InventoryItem.h"
#include "JoyWayTest/Weapon/Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "JoyWayTest/GameMode/JoyWayGameModeBase.h"
#include "JoyWayTest/HUD/HUDInterface.h"
#include "JoyWayTest/GameInstance/JoyWayGameInstance.h"


AJoyWayCharacter::AJoyWayCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 0.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

}

void AJoyWayCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CameraBoom->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, *FName(TEXT("headSocket")).ToString());

	OnTakeAnyDamage.AddDynamic(this, &AJoyWayCharacter::OnTakeAnyDamageHandle);

	AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>();

}

void AJoyWayCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJoyWayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AJoyWayCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJoyWayCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AJoyWayCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AJoyWayCharacter::LookUp);

	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AJoyWayCharacter::PickUp);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AJoyWayCharacter::Shoot);
	PlayerInputComponent->BindAction("ChangeLevel", IE_Pressed, this, &AJoyWayCharacter::ChangeLevel);

}

void AJoyWayCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}

void AJoyWayCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, Value);
	}
}

void AJoyWayCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AJoyWayCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AJoyWayCharacter::PickUp()
{
	if (auto Weapon = Cast<AWeapon>(OverlappingItem))
	{
		AttachWeapon(Cast<AWeapon>(OverlappingItem), Weapons.Add(Weapon));
	}
}

void AJoyWayCharacter::Shoot()
{
	for (auto Weapon : Weapons)
	{
		if (Weapon->WeaponState == EWeaponState::EWS_Equipped)
		{
			if (Weapon->Shoot())
			{
				JoyWayGameMode = Cast<AJoyWayGameModeBase>(GetWorld()->GetAuthGameMode());
				JoyWayGameMode->HUDInteface->SetAMMO(Weapon->GetAMMO());
			}
		}
	}
}

void AJoyWayCharacter::Init(TArray<TSubclassOf<AWeapon>> WeaponsInit, TArray<AInventoryItem*> InventoryItemsInit, float HealthInit, bool IsDeadInit, bool IsFirstLevelInit)
{
	if (Weapons.Num() != 0)
	{
		for (auto It : Weapons)
		{
			It->Destroy();
		}
	}
	for (auto It : WeaponsInit)
	{
		TSubclassOf<AWeapon> WeaponSubclass = AWeapon::StaticClass();
		
		FActorSpawnParameters SpawnParams;
		FTransform SpawnTransform = FTransform(FRotator(0.f, 0.f, 0.f), FVector(0.f, 0.f, 100.f));

		AWeapon* SpawnedWeapon = GetWorld()->SpawnActorDeferred<AWeapon>(WeaponSubclass, SpawnTransform, GetOwner(), nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		UGameplayStatics::FinishSpawningActor(SpawnedWeapon, SpawnTransform);
	}
	if (Weapons.Num() != 0)
	{
		AttachWeapon(Weapons.Last(), Weapons.Num() - 1);
	}

	if (InventoryItems.Num() != 0)
	{
		for (auto It : InventoryItems)
		{
			It->Destroy();
		}
	}
	InventoryItems = InventoryItemsInit;

	Health = HealthInit;
	IsDead = IsDeadInit;
	IsFirstLevel = IsFirstLevelInit;
}

void AJoyWayCharacter::PrintSMTH()
{
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("Player`s Health: %f"), Health));
}

TArray<AWeapon*> AJoyWayCharacter::GetWeapons()
{
	return Weapons;
}

TArray<AInventoryItem*> AJoyWayCharacter::GetInventoryItems()
{
	return InventoryItems;
}

float AJoyWayCharacter::GetHealth()
{
	return Health;
}

bool AJoyWayCharacter::GetIsDead()
{
	return IsDead;
}

bool AJoyWayCharacter::GetIsFirstLevel()
{
	return IsFirstLevel;
}

void AJoyWayCharacter::SetOverlappingWeapon(AInventoryItem* InventoryItem)
{
	if (OverlappingItem)
	{
		OverlappingItem->ShowPickupWidget(false);
	}

	OverlappingItem = InventoryItem;
	if (OverlappingItem)
	{
		OverlappingItem->ShowPickupWidget(true);
	}
}

void AJoyWayCharacter::ChangeLevel()
{
	auto GameInstance = Cast<UJoyWayGameInstance>(GetWorld()->GetGameInstance());
	
	GameInstance->LoadLevel((IsFirstLevel ? "SecondMap" : "FirstMap"), this);
}

void AJoyWayCharacter::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (!IsDead)
	{
		Health -= Damage;

		JoyWayGameMode = Cast<AJoyWayGameModeBase>(GetWorld()->GetAuthGameMode());
		JoyWayGameMode->HUDInteface->SetHealth(Health);

		if (Health <= 0)
		{
			IsDead = true;
			GetCharacterMovement()->DisableMovement();
			GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			GetMesh()->SetSimulatePhysics(true);

			JoyWayGameMode->SpawnCharacter(this);

			AActor* PlayerStarts = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass());
			AActor* SpawnedActor = GetWorld()->SpawnActor<AJoyWayCharacter>();
		}
	}
}

void AJoyWayCharacter::AttachWeapon(AWeapon* AttachingWeapon, int32 WeaponIndex)
{
	if (AttachingWeapon)
	{
		AttachingWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "hand_rSocket");
		AttachingWeapon->ShowPickupWidget(false);

		if (AWeapon* Weapon = Cast<AWeapon>(AttachingWeapon))
		{
			Weapon->WeaponState = EWeaponState::EWS_Equipped;

			if (WeaponIndex - 1 >= 0)
			{
				Weapons[WeaponIndex - 1]->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "spine_03Socket");
				Weapons[WeaponIndex - 1]->WeaponState = EWeaponState::EWS_NotEquipped;
			}
		}
	}
}