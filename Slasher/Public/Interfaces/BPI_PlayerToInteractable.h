// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_PlayerToInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UBPI_PlayerToInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SLASHER_API IBPI_PlayerToInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Player Interact Interface")
	void PlayerToInteractable_InputInteractPressed();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Player Interact Interface")
	void PlayerToInteractable_HighlightTrace();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Player Interact Interface")
	void PlayerToInteractable_CustomDepthFilterOn();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Player Interact Interface")
	void PlayerToInteractable_CustomDepthFilterOff();
};
