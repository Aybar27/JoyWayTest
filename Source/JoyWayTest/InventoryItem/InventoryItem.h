// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryItem.generated.h"

UCLASS()
class JOYWAYTEST_API AInventoryItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AInventoryItem();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ShowPickupWidget(bool bShowWidget);

	UFUNCTION()
	class USkeletalMeshComponent* GetMesh() const;

	UFUNCTION()
	FString GetMeshName() const;

	UFUNCTION()
	void SetMesh(FString MeshNameNew);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnSphereOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);

	UFUNCTION()
		void OnSphereEndOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex
		);

private:	
	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* AreaSphere;

	UPROPERTY(VisibleAnywhere)
		class UWidgetComponent* PickupWidget;

	UPROPERTY()
		FString MeshName;

};
