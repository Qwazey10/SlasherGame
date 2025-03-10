// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GlobalEnums.generated.h"


//Damage Type Enums,
UENUM(BlueprintType)
enum class EDamageType : uint8
{
	Null,
	DirectDamage_Physical,
	DirectDamage_Fire,
	DIRECTDAMAGE_Cold,
	DIRECTDAMAGE_Divine,
	DIRECTDAMAGE_DETRIMENTAL_Poison,
	DIRECTDAMAGE_DETRIMENTAL_Bleed,
	DIRECTDAMAGE_DETRIMENTAL_Fire,
	DIRECTDAMAGE_DETRIMENTAL_Cold,
};

UENUM(BlueprintType)
enum class EPlayerStatusType : uint8
{
	Normal,
	Burning,
	Poison,
	Bleed,
	Slowed,
};

//Equipment Slot Enums
UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
	Null UMETA(DisplayName="Null "),
	Helm UMETA(DisplayName="Helm -- 00"),
	Chest UMETA(DisplayName="Chest -- 01"),
	Arms UMETA(DisplayName="Arms -- 02"),
	Legs UMETA(DisplayName="Legs -- 03"),
	Boots UMETA(DisplayName="Boots -- 04"),
	Ring UMETA(DisplayName="Ring -- 05"),
	Primary UMETA(DisplayName="Primary -- 06"),
	Secondary UMETA(DisplayName="Secondary -- 07"),
	UsableItem UMETA(DisplayName="Usable Item -- 08"),
};

//Equipment Slot Enums
UENUM(BlueprintType)
enum class ESaveLocations : uint8
{
	SaveLocation_1 UMETA(DisplayName="Save Location 1"),
	SaveLocation_2 UMETA(DisplayName="Save Location 2"),
	SaveLocation_3 UMETA(DisplayName="Save Location 3"),
	SaveLocation_4 UMETA(DisplayName="Save Location 4"),
	SaveLocation_5 UMETA(DisplayName="Save Location 5"),
	SaveLocation_6 UMETA(DisplayName="Save Location 6")
};

UENUM(BlueprintType)
enum class EOnEquipPassive : uint8
{
	Null UMETA(DisplayName="Null"),
	HPRegeneration_Small UMETA(DisplayName="HP Regen Small"),
	HPRegeneration_Medium UMETA(DisplayName="HP Regen Medium"),
	HPRegeneration_Large UMETA(DisplayName="HP Regen Large"),
	ManaRegeneration_Small UMETA(DisplayName="MP Regen Small"),
	ManaRegeneration_Medium UMETA(DisplayName="MP Regen Medium"),
	ManaRegeneration_Large UMETA(DisplayName="MP Regen Large"),
	MovementSpeed_Small UMETA(DisplayName="Movement Speed Small"),
	MovementSpeed_Medium UMETA(DisplayName="Movement Speed Medium"),
	MovementSpeed_Large UMETA(DisplayName="Movement Speed Large"),
	DisableAllCasting UMETA(DisplayName="Disable All Casting"),
	DrainHP_Small UMETA(DisplayName="Drain HP Small"),
	DrainHP_Medium UMETA(DisplayName="Drain HP Medium"),
	DrainHP_Large UMETA(DisplayName="Drain HP Large"),
	GuardRegen_Small UMETA(DisplayName="Guard Regen Small"),
	GuardRegen_Medium UMETA(DisplayName="Guard Regen Medium"),
	GuardRegen_Large UMETA(DisplayName="Guard Regen Large"),
};

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	Null UMETA(DisplayName="Null"),
	Passive UMETA(DisplayName="Passive"),
	Duration UMETA(DisplayName="Duration"),
	Instant UMETA(DisplayName="Instant"),
};

UENUM(BlueprintType)
enum class EInventoryContext : uint8
{
	None UMETA(DisplayName="None"),
	BaseMenuContext UMETA(DisplayName="Base Menu Context"),
	UseItem UMETA(DisplayName="UseItem"),
	UseMagic UMETA(DisplayName="Use Magic"),
	Equipment UMETA(DisplayName="Equipment"),
	Stats UMETA(DisplayName="Stats"),
	DropItem UMETA(DisplayName="Drop Item"),
	Options UMETA(DisplayName="Options"),
	ReturnExit UMETA(DisplayName="Return/Exit"),
};

UENUM(BlueprintType)
enum class EMainMenuContext : uint8
{
	Start UMETA(DisplayName="Start"),
	Load UMETA(DisplayName="Load"),
	Settings UMETA(DisplayName="Settings"),
	Exit UMETA(DisplayName="Exit"),
};

UENUM(BlueprintType)
enum class EUseItemActionButtonContext : uint8
{
	UseItem UMETA(DisplayName="UseItem"),
	Drop UMETA(DisplayName="Drop"),
};

UENUM(BlueprintType)
enum class EEnemyAIAgentState : uint8
{
	None UMETA(DisplayName="UseItem"),
	Idle UMETA(DisplayName="Drop"),
	Wonder UMETA(DisplayName="Wondering"),
	Chase UMETA(DisplayName="Chasing"),
	Flee UMETA(DisplayName="Fleeing"),
	Ability UMETA(DisplayName="Using Ability"),
	Attacking UMETA(DisplayName="Attacking"),

	//	Moving       UMETA(DisplayName="Moving"),
	//	Dying        UMETA(DisplayName="Dying"),
	//	Dead         UMETA(DisplayName="Dead"),
	//	Respawning   UMETA(DisplayName="Respawning"),
};


