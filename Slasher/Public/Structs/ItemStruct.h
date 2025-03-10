// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityStruct.h"
#include "GlobalEnums.h"
#include "DataAssets/PhysicsInteractionAudioDataAsset.h"
#include "Engine/DataTable.h"
#include "Sound/SoundCue.h"
#include "ItemStruct.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct SLASHER_API FItemStruct : public FTableRowBase
{
	GENERATED_BODY()

	//Basic Item Definitions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Descriptions")
	int ItemID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Descriptions")
	EEquipmentSlot EquipSlot = EEquipmentSlot::Null;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Descriptions")
	FString ItemName = "ItemName";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Descriptions")
	FString ItemDescription = "ItemDescription";


	//Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Attributes")
	float Health = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Attributes")
	float Mana = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Attributes")
	float Guard = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Attributes")
	float Strength = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Attributes")
	float Stamina = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Attributes")
	float Dexterity = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Attributes")
	float Intelligence = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Attributes")
	bool bHasUniqueMod = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Attributes")
	EOnEquipPassive OnEquipPassive = EOnEquipPassive::Null;


	//Damage Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Attributes")
	float Damage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Attributes")
	float AttackSpeed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Attributes")
	float MagicDmgMod = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Attributes")
	EDamageType WeaponDamageType_Primary = EDamageType::Null;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Attributes")
	EDamageType WeaponDamageType_Secondary = EDamageType::Null;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Attributes")
	float PrimaryStatusModAmt = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Attributes")
	float SecondaryStatusModAmt = 0;

	//Defensive Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defensive Attributes")
	float Armor = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defensive Attributes")
	float Resist_Fire = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defensive Attributes")
	float Resist_Cold = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defensive Attributes")
	float Resist_Detrimental = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defensive Attributes")
	float Resist_Divine = 0;


	//Utilities
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility Attributes")
	float SalePrice = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility Attributes")
	float Weight = 0;


	//Ability Power Modifications
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnUse Ability Attributes")
	int OnUse_ActivateAbilityID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnUse Ability Attributes")
	float Power = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnUse Ability Attributes")
	FString Description_00 = "Item Description_01";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnUse Ability Attributes")
	float AbilityMod_00 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnUse Ability Attributes")
	FString Description_01 = "Item Description_01";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnUse Ability Attributes")
	float AbilityMod_01 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnUse Ability Attributes")
	FString Description_02 = "Item Description_02";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnUse Ability Attributes")
	float AbilityMod_02 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnUse Ability Attributes")
	FString Description_03 = "Item Description_03";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OnUse Ability Attributes")
	float AbilityMod_03 = 0;

	//Static Mesh Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	UStaticMesh* ItemDisplayMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	FTransform ItemDisplayMeshTransform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	bool bHasOnEquipPassive = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	UNiagaraSystem* OnEquip_NiagaraSystem = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	float BuoyancyPontoonSize = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	float ItemPhysicsMass = 200.0f;


	//Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundCue* ItemUseSound = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundCue* ItemPickUpSound = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundCue* ItemDestroySound = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundAttenuation* ItemAttenuation = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")
	UPhysicsInteractionAudioDataAsset* InteractionAudioDataAsset = nullptr;

	// Reference to Texture2D (can be set in Data Table)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")
	UTexture2D* Texture = nullptr;


	FItemStruct();
	virtual ~FItemStruct() override;
};
