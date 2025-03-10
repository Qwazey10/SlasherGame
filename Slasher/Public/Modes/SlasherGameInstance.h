// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Containers/StaticArray.h"
#include "GlobalEnums.h"
#include "Engine/DataTable.h"
#include "SlasherGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SLASHER_API USlasherGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	//Inventory Related Vars

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slasher Inventory")
	TArray<int> Inventory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	int InventorySize = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	TArray<int> Equipment;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save / Load Vars")
	FVector4 SaveLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save / Load Vars")
	ESaveLocations SaveLocations;
	//Character Vars
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
	float GI_CurrentExperience = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
	int GI_CurrentLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
	int Gold = 420;

	//Item Data Table
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTables")
	UDataTable* ItemDataTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTables")
	UDataTable* ExperienceDataTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTables")
	UDataTable* EnemyDataTable;

	// USE ITEM CONTEXT BUTTON VARS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Use Item Context Button Vars")
	int GI_ClickedItemID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Use Item Context Button Vars")
	int GI_ClickedItemInventoryIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Use Item Context Button Vars")
	UUserWidget* UseItemContextWidget;


	//Debug Variables
	
	//This governs if we show the Trace from the weapon attack. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bShowWeaponActorAttackTraceDebug = false;
	
	virtual void Init() override;

	// Override the Shutdown function
	virtual void Shutdown() override;

	//Save and Load Functions
	//void SaveGame();
	//void LoadGame();
};
