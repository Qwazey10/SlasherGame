// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LevelUpStruct.generated.h"


/**
 *					CHARACTER LEVEL UP STUCT, Used To Plot Gains on Level Up
 */
USTRUCT(BlueprintType)
struct SLASHER_API FLevelUpStruct: public FTableRowBase
{
public:
	
	GENERATED_BODY()

	
	//Experience To Next Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experience")
	float ExperienceToNextLevel = 0;

	
	//Base Attributes At X Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes At X Level")
	float BaseHealthAtLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes At X Level")
	float BaseManaAtLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes At X Level")
	float BaseStrengthAtLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes At X Level")
	float BaseStaminaAtLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes At X Level")
	float BaseDexterityAtLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes At X Level")
	float BaseIntelligenceAtLevel = 0;

	
	//Offenses 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Offenses At X Level")
	float BaseAttackSpeedAtLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Offenses At X Level")
	float BaseMagicDmgModAtLevel = 0;

	
	//Defenses 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defenses At X Level")
	float BaseArmorAtLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defenses At X Level")
	float BaseFireResistAtLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defenses At X Level")
	float BaseColdResistAtLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defenses At X Level")
	float BaseDetrimentalResistAtLevel = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defenses At X Level")
	float BaseDivineResistAtLevel = 0;
	
	
	
	FLevelUpStruct();
	~FLevelUpStruct();
};

