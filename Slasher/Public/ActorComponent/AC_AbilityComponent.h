// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEnums.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"

class AEnemyBase;
class ASlasherCharacter;
#include "AC_AbilityComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLASHER_API UAC_AbilityComponent : public UActorComponent

{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_AbilityComponent();
	//Owner Reference

	//if component is attached to Character, this will be Reference. 


	
	
	
	//UtilityLineTraceFunction 
	FHitResult Utility_LineTrace(FVector StartLoc, FVector EndLoc, EDrawDebugTrace::Type TraceType,float TraceDistance, float DrawTime) const;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	void ExecuteAbilityID(
		int AbilityID,
		EAbilityType InputAbilityType,
		float InputRange,
		float InputCooldown,
		float InputDuration,
		float TickRate,
		float AbilityMod00,
		float AbilityMod01,
		float AbilityMod02,
		float AbilityMod03);
	void Grant_Experience_AbilityID_001(float AmtOfEXPToAdd);
	void SetMovementSpeed(float WalkSpeedSet);
};
