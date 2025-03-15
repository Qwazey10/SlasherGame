// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_DamageInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBPI_DamageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SLASHER_API IBPI_DamageInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DeathOfOwner();

	//Start Call Functions
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DmgInterfaceApplyEffectCosmeticBurning();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DmgInterfaceApplyEffectCosmeticBleed();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DmgInterfaceApplyEffectCosmeticPoison();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DmgInterfaceApplyEffectCosmeticFrost();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DmgInterfaceApplyEffectCosmeticBurning_End();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DmgInterfaceApplyEffectCosmeticBleed_End();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DmgInterfaceApplyEffectCosmeticPoison_End();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DmgInterfaceApplyEffectCosmeticFrost_End();
};
