// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEnums.h"
#include "Engine/DataTable.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundCue.h"
#include "AbilityStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct SLASHER_API FAbilityStruct : public FTableRowBase
{
	GENERATED_BODY()


	//Ability Description

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Description")
	int AbilityID = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Description")
	FString AbilityName = "AbilityName";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Description")
	FString AbilityDescription = "Ability Description";


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Ability Attributes")
	EAbilityType AbilityType = EAbilityType::Null;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Ability Attributes")
	float ManaCost = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Ability Attributes")
	float Range = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Mod Values")
	float Cooldown = 30;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Mod Values")
	float TickRate = 6;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability Mod Values")
	float Duration = 30;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Mod Values")
	FString PrimaryAbilityMod_Description = "Description for What the Primary Ability Mod Does";
	// The amount of damage or healing the ability does
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Mod Values")
	float PrimaryAbility_Mod = 9;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	FString AbilityMod_00_Description = "Description for Ability Mod 00 Value";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float AbilityMod_00 = 1.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Mod Values")
	FString AbilityMod_01_Description = "Description for Ability Mod 01 Value";
	// The amount of damage or healing the ability does
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Mod Values")
	float AbilityMod_01 = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Mod Values")
	FString AbilityMod_02_Description = "Description for Ability Mod 02 Value";
	// The amount of damage or healing the ability does
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Mod Values")
	float AbilityMod_02 = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Mod Values")
	FString AbilityMod_03_Description = "Description for Ability Mod 03 Value";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Mod Values")
	float AbilityMod_03 = 1.0f;


	//Appearance References. 

	// The icon representing the ability in the UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	UTexture2D* AbilityIcon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	UTexture2D* BuffBar_AbilityIcon = nullptr;

	// The animation to play when the ability is activated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	UAnimMontage* AbilityAnimation = nullptr;

	// The sound to play when the ability is activated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	USoundCue* AbilitySound = nullptr;

	// The particle system to spawn when the ability is activated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	UNiagaraSystem* MyNiagaraSystem = nullptr;


	FAbilityStruct();
	virtual ~FAbilityStruct() override;
};
