// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JoyWayGameModeBase.generated.h"

class AJoyWayCharacter;

UCLASS()
class JOYWAYTEST_API AJoyWayGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	UFUNCTION(BlueprintCallable)
		void SpawnCharacter(AJoyWayCharacter* Character);

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUserWidget> WidgetClass;
	
	UPROPERTY()
		class UHUDInterface* HUDInteface;
};
