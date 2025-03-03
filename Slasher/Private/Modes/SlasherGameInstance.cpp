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
	Equipment = {0, 0, 0, 0, 0, 0, 0, 0, 0 };
	UE_LOG(LogTemp, Warning, TEXT("Init Equipment Inventory	"));
	int EquipmentSize = Equipment.Num();
	UE_LOG(LogTemp, Warning, TEXT("Equipment Size: %d"), EquipmentSize);
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Initialized!"));
	Inventory.Insert(2, 3);
	Inventory.Insert(10, 4);
	Inventory.Insert(11, 6);
	Inventory.Insert(12, 7);
	Inventory.Insert(10, 8);
	Inventory.Insert(10, 9);
	Inventory.Insert(10, 10);
	Inventory.Insert(10, 11);
	Inventory.Insert(10, 12);
	
}

void USlasherGameInstance::Shutdown()
{
	Super::Shutdown();

	// Custom cleanup logic
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Shutdown!"));
}