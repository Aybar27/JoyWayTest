// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "JoyWayTest/Character/JoyWayCharacter.h"

AInventoryItem::AInventoryItem()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(Mesh);
	
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(RootComponent);
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AInventoryItem::OnSphereOverlap);
	AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AInventoryItem::OnSphereEndOverlap);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	PickupWidget->SetupAttachment(RootComponent);

}

void AInventoryItem::SetMesh(FString MeshNameNew)
{
	Mesh = LoadObject<USkeletalMeshComponent>(nullptr, TEXT("/Game/Assets/MilitaryWeapSilver/Weapons/Assault_Rifle_A"));

	/*if (Mesh)
	{
		GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Green, FString::Printf(TEXT("NotEmpty: %s"), *Mesh->GetFName().ToString()));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("NotSpawned")));
	}*/
}

void AInventoryItem::BeginPlay()
{
	Super::BeginPlay();
}

void AInventoryItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInventoryItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AJoyWayCharacter* JoyWayCharacter = Cast<AJoyWayCharacter>(OtherActor);
	if (JoyWayCharacter)
	{
		JoyWayCharacter->SetOverlappingWeapon(this);
	}
}

void AInventoryItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AJoyWayCharacter* JoyWayCharacter = Cast<AJoyWayCharacter>(OtherActor);
	if (JoyWayCharacter)
	{
		JoyWayCharacter->SetOverlappingWeapon(nullptr);
	}
}

void AInventoryItem::ShowPickupWidget(bool bShowWidget)
{
	if (PickupWidget)
	{
		PickupWidget->SetVisibility(bShowWidget);
	}
}

USkeletalMeshComponent* AInventoryItem::GetMesh() const
{
	return Mesh;
}

FString AInventoryItem::GetMeshName() const
{
	return Mesh->GetFName().ToString();
}

