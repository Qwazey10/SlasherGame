// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalUtils.h"

float GlobalUtils::CalculateBaseDamage(
	float BaseDamage,
	EDamageType PrimaryDamageType,
	float Armor,
	float ResistFire,
	float ResistCold,
	float ResistDetrimental,
	float ResistDivine
	)

{

}


float GlobalUtils::CalculateStatus(float AttackerStatusBuild, float DefenderStatusAmt,
                                  float DefenderStatusResist)
{
	float StatusDamage = AttackerStatusBuild * 1  (DefenderStatusAmt * (1.0f - (DefenderStatusResist / 100.0f)));
	return StatusDamage;
}




GlobalUtils::GlobalUtils()
{
}

GlobalUtils::~GlobalUtils()
{
}
		