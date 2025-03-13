// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/AC_AbilityComponent.h"
#include "Interfaces/BPI_PlayerToEnemy.h"
#include "Interfaces/BPI_DamageInterface.h"
#include "GameFramework/Character.h"
#include "GlobalEnums.h"
#include "EnemyBase.generated.h"


class UAC_AbilityComponent;

UCLASS()
class SLASHER_API AEnemyBase : public ACharacter, public IBPI_PlayerToEnemy, public IBPI_DamageInterface
{
	GENERATED_BODY()

public:
	// Constructor
	AEnemyBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	USkeletalMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	UStaticMeshComponent* PrimaryEquipmentMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Appearance")
	UStaticMeshComponent* SecondaryEquipmentMesh;

	//Set up Base Attributes. 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float CurrentHealth = 6969;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float CurrentMana = 420;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float EnemyBaseArmor = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float EnemyBaseResistFire = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float EnemyBaseResistCold = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float EnemyBaseResistDetrimental = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float EnemyBaseResistDivine = 0;

	//Status Buildup
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float EnemyStatPoisonBuildup = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float EnemyStatBurnBuildup = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float EnemyStatBleedBuildup = 0.0f;
	
	//AI
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	EEnemyAIAgentState CurrentState = EEnemyAIAgentState::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float TurnRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float CurrentStateTime = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float CurrentStateDuration = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float CurrentStateCooldown = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float CurrentStateTickRate = 0.0f;

	FTimerHandle StateChangeTimerHandle;

	void CheckAIStateChange() const;
	void StartCheckStateChangeTimer();

	//Enemy Actor Components. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Components")
	UAC_AbilityComponent* AbilityComponent;

	//Interfaces
	IBPI_PlayerToEnemy* PlayerToEnemyInterface;

protected:
	// Called when the game starts or when spawnedEditAnywhere
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//BPI_PlayerToEnemy Interface Functions

	virtual void PlayerToEnemyInterface_Attack_Implementation(AActor* InstigatingActor, float BaseWeaponDamage, EDamageType PrimaryDamageType,float PrimaryStatusAmt, EDamageType SecondaryDamageType, float SecondaryStatusAmt) override;

	void DamageTaken(float DamageAmount, AActor* DamageInstigator, EDamageType PrimaryDamageType, float PrimaryDamageTypeStatusAmt, EDamageType SecondaryDamageType, float SecondaryDamageTypeStatusAmt);
	void KillEnemyBase();

	//Status Effect Functions
	
	//Burning
	void TriggerBurningEffect();
	//Bleeding Effect Trigger
	void TriggerBleedingEffect();
	//Poison Effect Trigger
	void TriggerPoisonEffect();
	//FrostEffectTrigger
	void TriggerFrostEffect();

};
