// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Sound/SoundCue.h"
#include "InventoryUIDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UInventoryUIDataAsset : public UPrimaryDataAsset
{
public:
	
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	USoundCue* WidgetMouseHoverAudio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	USoundCue* WidgetMouseClickAudio;

	
};
