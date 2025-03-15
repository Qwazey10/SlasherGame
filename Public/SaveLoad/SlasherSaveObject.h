// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SlasherSaveObject.generated.h"

/**
 * 
 */
UCLASS()
class SLASHER_API USlasherSaveObject : public USaveGame
{
	GENERATED_BODY()

public:
	//Player Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	FVector SavObjPlayerLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	FRotator SavObjPlayerRotation;

	//Equipment
	TArray<int>SavObjEquipment;
	
	//Inventory
	TArray<int>SavObjInventory;
};
