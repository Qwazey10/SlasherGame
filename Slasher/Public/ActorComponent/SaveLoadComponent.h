// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SaveLoadComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLASHER_API USaveLoadComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USaveLoadComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FTimerHandle AutoSaveTimerHandle;
	//Save and Load Functions

	// Sav Func
	void SaveGame(FString& SlotName);
	// Load Func
	void LoadGame(FString& SlotName);

	//Create Save Game Object
	void SlasherCreateSaveGameObject(FString& SlotName);

	//Delete Save Game Object
	void SlasherDeleteSaveGameObject(FString& SlotName);

	void SlasherAutoSave();
};
