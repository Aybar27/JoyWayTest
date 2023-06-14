// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "JoyWayTest/InventoryItem/InventoryItem.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

bool AWeapon::Shoot()
{
	if (AMMO <= 0) return false;

	if (!GetWorld()) return false;
	
	const FTransform SocketTransform = GetMesh()->GetSocketTransform("MuzzleFlash");
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);

	if (HitResult.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 24, FColor::Red, false, 5.0f);
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), 1, nullptr, this, UDamageType::StaticClass());
	}

	--AMMO;

	return true;
}

int32 AWeapon::GetAMMO()
{
	return AMMO;
}

