// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDInterface.generated.h"

/**
 * 
 */
UCLASS()
class JOYWAYTEST_API UHUDInterface : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Health;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* AMMO;

public:
	UFUNCTION()
		void SetHealth(float HealthNew);

	UFUNCTION()
		void SetAMMO(int AMMONew);
};
