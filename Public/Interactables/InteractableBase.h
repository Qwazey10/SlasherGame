// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorComponent/DamageComponent.h"
#include "DataAssets/PhysicsInteractionAudioDataAsset.h"
#include "GameFramework/Actor.h"
#include "Interfaces/BPI_DamageInterface.h"
#include "Interfaces/BPI_PlayerToEnemy.h"
#include "Interfaces/BPI_PlayerToInteractable.h"
#include "InteractableBase.generated.h"

UCLASS()
class SLASHER_API AInteractableBase : public AActor ,public IBPI_PlayerToInteractable, public IBPI_PlayerToEnemy, public IBPI_DamageInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* InteractableBaseMesh;

	//Audio Data Asset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicsInteractionAudio - DataAsset")
	UPhysicsInteractionAudioDataAsset* PhysicsInteractionAudioDataAsset;
	
	//Vars for the damage system
	UPROPERTY (EditAnywhere, BlueprintReadWrite, Category = "Damage System Attributes")
	float InteractableBaseHealth = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage System Attributes")
	float InteractableBaseDamage = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage System Attributes")
	float InteractableBaseArmor = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage System Attributes")
	float InteractableBaseFireResist = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage System Attributes")
	float InteractableBaseColdResist = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage System Attributes")
	float InteractableBaseDetrimentalResist = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage System Attributes")
	float InteractableBaseDivineResist = 0;


	//Immunity Booleans
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage System Attributes")
	bool bIsInteractableImmuneFire = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage System Attributes")
	bool bIsInteractableImmuneCold = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage System Attributes")
	bool bIsInteractableImmuneBleed = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage System Attributes")
	bool bIsInteractableImmuneMagic = false;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Component")
	UDamageComponent* DamageComponent;

	virtual void PlayerToEnemyInterface_Attack_Implementation(AActor* InstigatingActor, float BaseWeaponDamage, EDamageType PrimaryDamageType,float PrimaryStatusAmt, EDamageType SecondaryDamageType, float SecondaryStatusAmt) override;

	virtual void DeathOfOwner_Implementation();

	void SetupDamageComponentDefensives();
	
	virtual void PlayerToInteractable_InputInteractPressed_Implementation() override;
	virtual void PlayerToInteractable_HighlightTrace_Implementation() override;
	virtual void PlayerToInteractable_CustomDepthFilterOn_Implementation() override;
	virtual void PlayerToInteractable_CustomDepthFilterOff_Implementation() override;

	//Damage Functions

	void DestroyInteractable();
};
