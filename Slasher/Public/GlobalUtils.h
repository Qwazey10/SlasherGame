// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEnums.h"

/**
 * 
 */
class SLASHER_API GlobalUtils
{
	GlobalUtils();
	~GlobalUtils();
	
public:
	
	static float CalculateBaseDamage(
		float BaseDamage,
		EDamageType PrimaryDamageType,
		float Armor,
		float ResistFire,
		float ResistCold,
		float ResistDetrimental,
		float ResistDivine);
		
	static bool CalculateStatus(
		float AttackerStatusBuild,
		float DefenderStatusAmt,
		float DefenderStatusResist
		);
	

	



	

};
