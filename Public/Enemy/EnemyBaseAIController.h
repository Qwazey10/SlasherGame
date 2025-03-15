// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyBaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class SLASHER_API AEnemyBaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	void FindRandomPointInRadius(float RandRadius);
};
