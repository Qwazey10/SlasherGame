// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEnums.h"
#include "Actors/WeaponActor.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "EquipmentComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLASHER_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDataTable")
	UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipped Actor References")
	AWeaponActor* PrimaryWeaponActorReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipped Actor References")
	AWeaponActor* SecondaryWeaponActorReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "A Weapon Actor Class Reference")
	TSubclassOf<AWeaponActor> WeaponClass;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	 * This Function is used to spawn in the weapon actors that are attached to the Primary and Secondary Components on the base mesh.
	 * Index determines which slot to assign, 0 = Primary Slot Ref, 1 = Secondary Slot Ref. 
	 */
	void EquipItem_SpawnEquipMesh(int Index, int PrimaryItemIDToEquip);

	/*
	 * This Function Loops the equipment array and sets up base stats on the Character reference, This is set up to work on SlasherCharacter for Now. Maybe Port to EnemyBase. 
	 */
	void SetupEquipmentAttributes();

	/*
	 * This Function is for setting up Equipment Unique Passives if there are any assigned on available equipment. 
	 */
	void SwitchOnEquipPassive(EOnEquipPassive PassiveEffect);
};
