// Fill out your copyright notice in the Description page of Project Settings.


#include "JoyWayGameModeBase.h"
#include "JoyWayTest/Character/JoyWayCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "JoyWayTest/HUD/HUDInterface.h"
#include "JoyWayTest/GameInstance/JoyWayGameInstance.h"

void AJoyWayGameModeBase::BeginPlay()
{
	HUDInteface = CreateWidget<UHUDInterface>(GetWorld(), WidgetClass, "HUDInterface");

	HUDInteface->AddToViewport();
}

void AJoyWayGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UJoyWayGameInstance* GameInstance = Cast<UJoyWayGameInstance>(GetGameInstance());
}

void AJoyWayGameModeBase::SpawnCharacter(AJoyWayCharacter* Character)
{

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto Controller = Character->GetController();

	if (Controller)
	{
		Character->Destroy();
		RestartPlayer(Controller);
	}
}
