// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEnums.h"
#include "UObject/Interface.h"

#include "BPI_PlayerToEnemy.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UBPI_PlayerToEnemy : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SLASHER_API IBPI_PlayerToEnemy
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PlayerToEnemyInterface_Attack(AActor* InstigatingActor, float BaseWeaponDamage, EDamageType PrimaryDamageType,float PrimaryStatusAmt, EDamageType SecondaryDamageType, float SecondaryStatusAmt);
};
