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
	switch (PrimaryDamageType)
	{
	case EDamageType::Null:
		{
			GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red,
				"GlobalUtils.cpp -- CalculateDamage -- PrimaryDamageType is Null, Add Damage Type to PrimaryItemDatabase");
			return BaseDamage;
		}

	case EDamageType::DirectDamage_Physical:
		{
			const float TotalDamage = BaseDamage * (Armor / 100.0f) / 100.0f;
			return TotalDamage;
		}

	case EDamageType::DirectDamage_Fire:
		{
			const float TotalDamageFire = BaseDamage * (ResistFire / 100.0f) / 100.0f;
			return TotalDamageFire;
		}

	case EDamageType::DIRECTDAMAGE_Cold:
		{
			const float TotalDamageCold = BaseDamage * (ResistCold / 100.0f) / 100.0f;
			return TotalDamageCold;
		}

	case EDamageType::DIRECTDAMAGE_Divine:
		{
			const float TotalDamageDivine = BaseDamage * (ResistDivine / 100.0f) / 100.0f;
			return TotalDamageDivine;
		}

	case EDamageType::DIRECTDAMAGE_DETRIMENTAL_Poison:
		{
			// Detrimental effects ignore armor but can be influenced by other factors
			const float TotalDamagePoison = BaseDamage * (1.0f - (ResistDetrimental / 100.0f));
			return TotalDamagePoison;
		}

	case EDamageType::DIRECTDAMAGE_DETRIMENTAL_Bleed:
		{
			// Detrimental effects ignore armor but can be influenced by other factors
			const float TotalDamageBleed = BaseDamage * (1.0f - (ResistDetrimental / 100.0f));
			return TotalDamageBleed;
		}

	case EDamageType::DIRECTDAMAGE_DETRIMENTAL_Fire:
		{
			const float TotalDamageDetrimentalFire = BaseDamage * (1.0f - ((ResistDetrimental + ResistFire) / 100.0f));
			return TotalDamageDetrimentalFire;
		}

	case EDamageType::DIRECTDAMAGE_DETRIMENTAL_Cold:
		{
			const float TotalDamageDetrimentalCold = BaseDamage * (1.0f - ((ResistDetrimental + ResistCold) / 100.0f));
			return TotalDamageDetrimentalCold;
		}

	default:
		return BaseDamage;
	}
}


bool GlobalUtils::CalculateStatus(float AttackerStatusBuild, float DefenderStatusAmt,
                                  float DefenderStatusResist)
{
	bool bInflictStatus =  AttackerStatusBuild > (DefenderStatusAmt * (1.0f - (DefenderStatusResist / 100.0f)));
	return bInflictStatus;
}




GlobalUtils::GlobalUtils()
{
}

GlobalUtils::~GlobalUtils()
{
}
		