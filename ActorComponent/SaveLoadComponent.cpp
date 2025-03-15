// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/SaveLoadComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Modes/SlasherGameInstance.h"
#include "SaveLoad/SlasherSaveObject.h"

// Sets default values for this component's properties
USaveLoadComponent::USaveLoadComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void USaveLoadComponent::BeginPlay()
{
	Super::BeginPlay();
		
	GetWorld()->GetTimerManager().SetTimer(
	AutoSaveTimerHandle, 
	this, 
	&USaveLoadComponent::SlasherAutoSave,
	30,
	true
	);
}

void USaveLoadComponent::SlasherAutoSave()
{
	FString SlotName = "Autosave";
	SaveGame(SlotName);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, "AutoSave Function Called");
	}
}



// Called every frame
void USaveLoadComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void USaveLoadComponent::SaveGame(FString& SlotName)
{
	
	// Check if a save game object already exists in memory
	USlasherSaveObject* SlasherSaveGameObject = Cast<USlasherSaveObject>(UGameplayStatics::CreateSaveGameObject(USlasherSaveObject::StaticClass()));
	
	if (SlasherSaveGameObject)
	{
		USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(GetWorld()->GetGameInstance());
		
		if (SlasherGI)
		{
			SlasherSaveGameObject->SavObjInventory = SlasherGI->Inventory;
			SlasherSaveGameObject->SavObjEquipment = SlasherGI->Equipment;
			SlasherSaveGameObject->SavObjPlayerLocation = GetOwner()->GetActorLocation();
			SlasherSaveGameObject->SavObjPlayerRotation = GetOwner()->GetActorRotation();
		}
	}
	else
	{
		// Failed to create save game object
		UE_LOG(LogTemp, Error, TEXT("Failed to create save game object."));
	}

	// Save the game object to the save slot
	bool bSaveSuccessful = UGameplayStatics::SaveGameToSlot(SlasherSaveGameObject, SlotName, 0);
	
	if (bSaveSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Save Successful"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Save Failed"));
	}
}

void USaveLoadComponent::LoadGame(FString& SlotName)
{
	USlasherSaveObject* SlasherLoadedGame = Cast<USlasherSaveObject>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	if (SlasherLoadedGame)
	{
		USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(GetWorld()->GetGameInstance());
		SlasherGI->Inventory = SlasherLoadedGame->SavObjInventory;
		SlasherGI->Equipment = SlasherLoadedGame->SavObjEquipment;
		GetOwner()->SetActorLocation(SlasherLoadedGame->SavObjPlayerLocation);
		GetOwner()->SetActorRotation(SlasherLoadedGame->SavObjPlayerRotation);
		UE_LOG(LogTemp, Warning, TEXT("Load Successful"));
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Load Failed"));
	}
}

void USaveLoadComponent::SlasherCreateSaveGameObject(FString& SlotName)
{
	//Delete Maybe
}

void USaveLoadComponent::SlasherDeleteSaveGameObject(FString& SlotName)
{
	//Delete Maybe
}




