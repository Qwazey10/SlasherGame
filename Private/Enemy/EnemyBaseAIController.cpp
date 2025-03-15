// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBaseAIController.h"
#include "DrawDebugHelpers.h"
#include "NavigationSystem.h"

void AEnemyBaseAIController::FindRandomPointInRadius(float RandRadius)
{
	FVector Origin = GetPawn() ? GetPawn()->GetActorLocation() : FVector::ZeroVector;
	FVector RandomPoint;
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	if (NavSystem && NavSystem->K2_GetRandomReachablePointInRadius(GetWorld(), Origin, RandomPoint, RandRadius))
	{
		UE_LOG(LogTemp, Log, TEXT("Found Random Point: %s"), *RandomPoint.ToString());

		MoveToLocation(RandomPoint, 5.0f);
		DrawDebugSphere(GetWorld(), RandomPoint, RandRadius, 10, FColor::Yellow, false, 10.0f);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find random reachable point in radius!"));
	}
}
