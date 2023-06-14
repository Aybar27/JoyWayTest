// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDInterface.h"
#include "JoyWayTest/Character/JoyWayCharacter.h"
#include "Components/TextBlock.h"

void UHUDInterface::SetHealth(float HealthNew) 
{
	Health->SetText(FText::FromString(FString::SanitizeFloat(FMath::Clamp(HealthNew, 0.f, 100.f))));
}

void UHUDInterface::SetAMMO(int AMMONew)
{
	AMMO->SetText(FText::FromString(FString::FromInt(AMMONew)));
}

