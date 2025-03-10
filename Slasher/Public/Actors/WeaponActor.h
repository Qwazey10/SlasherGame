// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "Structs/ItemStruct.h"
#include "WeaponActor.generated.h"

UCLASS()
class SLASHER_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init Vars")
	int WeaponID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Item DataTable")
	UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Item DataTable")
	float WeaponActorDamage;

	//Primary Damage Type from DT Item Data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Data")
	EDamageType PrimaryDamageType;
	
	//Status Amount From DT Item Data
	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = "Item Data")
	float PrimaryDamageStatusAmt;

	//Secondary Damage Type from DT Item Data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Data")
	EDamageType SecondaryDamageType;

	//Status Amount From DT Item Data
	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = "Item Data")
	float SecondaryDamageStatusAmt;

	void OnConstruct_SetupAppearanceAndAttributes(int ItemID);

	virtual void OnConstruction(const FTransform& Transform) override;
	
	//Attack Functions
	void AttackTrace();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
