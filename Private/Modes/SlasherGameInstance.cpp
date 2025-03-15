// Fill out your copyright notice in the Description page of Project Settings.


#include "Modes/SlasherGameInstance.h"


void USlasherGameInstance::Init()
{
	Super::Init();
	//Inventory = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // init inventory array, 20 slots
	// Custom initialization logic
	//

	//Inventory.Insert(2, 2); function to add an item to inventory. 


	for (int i = 0; i < InventorySize; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory[%d]"), i);
		Inventory.Insert(0, i);
	}
	int Length = Inventory.Num();
	UE_LOG(LogTemp, Warning, TEXT("Inventory Size: %d"), Length);


	//Init Equipment
	//Null          UMETA(DisplayName="Null "),
	//Helm          UMETA(DisplayName="Helm -- 00"),
	//Chest         UMETA(DisplayName="Chest -- 01"),
	//Arms          UMETA(DisplayName="Arms -- 02"),
	//Legs          UMETA(DisplayName="Legs -- 03"),
	//Boots         UMETA(DisplayName="Boots -- 04"),
	//Ring          UMETA(DisplayName="Ring -- 05"),
	//Primary       UMETA(DisplayName="Primary -- 06"),
	//Secondary     UMETA(DisplayName="Secondary -- 07"),
	//UsableItem    UMETA(DisplayName="Usable Item -- 08"),
	
	Equipment = {0, 0, 0, 0, 0, 0, 8, 0, 0};
	
	UE_LOG(LogTemp, Warning, TEXT("Init Equipment Inventory	"));
	int EquipmentSize = Equipment.Num();
	UE_LOG(LogTemp, Warning, TEXT("Equipment Size: %d"), EquipmentSize);
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Initialized!"));
	Inventory[1] = 10;

}

void USlasherGameInstance::Shutdown()
{
	Super::Shutdown();
	
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Shutdown!"));
}
