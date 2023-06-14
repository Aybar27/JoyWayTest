// Fill out your copyright notice in the Description page of Project Settings.


#include "JoyWayGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "JoyWayTest/Character/JoyWayCharacter.h"
#include "JoyWayTest/GameMode/JoyWayGameModeBase.h"
#include "JoyWayTest/Weapon/Weapon.h"
#include "JoyWayTest/InventoryItem/InventoryItem.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

void UJoyWayGameInstance::LoadLevel(FName LevelName, ACharacter* Character)
{
    AJoyWayCharacter* JoyWayCharacter = Cast<AJoyWayCharacter>(Character);

    UGameplayStatics::OpenLevel(GetWorld(), LevelName);

    for (auto It : JoyWayCharacter->GetWeapons())
    {
        TSubclassOf<AWeapon> Weapon = It->StaticClass();

        /*GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Blue, FString::Printf(TEXT("Subclass: %s, %s"),
            *It->StaticClass()->GetDisplayNameText().ToString(), *Weapon->StaticClass()->GetDisplayNameText().ToString()));
        */
        Weapons.Add(Weapon);
    }

    InventoryItems = JoyWayCharacter->GetInventoryItems();
    Health = JoyWayCharacter->GetHealth();
    IsDead = JoyWayCharacter->GetIsDead();
    IsFirstLevel = !JoyWayCharacter->GetIsFirstLevel();
    
    Cast<AJoyWayCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Init(Weapons, InventoryItems, Health, IsDead, IsFirstLevel);
}
