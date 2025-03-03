// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/BPI_PlayerToInteractable.h"
#include "Structs/ItemStruct.h"
#include "DataAssets/PhysicsInteractionAudioDataAsset.h"
#include "Engine/DataTable.h"
#include "BuoyancyComponent.h"

#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

UCLASS()
class SLASHER_API AItemActor : public AActor , public IBPI_PlayerToInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();


	//Item Inits 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemActor Init")
	FItemStruct Struct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemActor Init")
	int SpawnItemID;
	
	IBPI_PlayerToInteractable* PlayerToInteractable; // Player to Interactable Interface
	
	
	//Mesh and DataTable 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Item DataTable")
	UDataTable* ItemDataTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Mesh;


	// Audio References
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundCue* ItemUseSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundCue* ItemPickUpSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundCue* ItemDestroySound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundAttenuation* ItemAttenuation;

	//Basic Item Definitions
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		
	int ItemID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemDescription;

	//Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Mana; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Strength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Dexterity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Intelligence;

	//Damage Attributes
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MagicDmgMod;
	
	//Defensive Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Armor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Resist_Fire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Resist_Cold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Resist_Detrimental;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Resist_Divine;

	//Ability Power Modifications
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int OnUse_ActivateAbilityID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Power; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description_00;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AbilityMod_00;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description_01;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AbilityMod_01;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description_02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AbilityMod_02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description_03;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AbilityMod_03;
	
	//Utilities
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SalePrice;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector PhysicsImpactLocation;
	
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bDebugImpacts = false;


	FSphericalPontoon Pontoon_00;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//BP Style Constructor
	virtual void OnConstruction(const FTransform& Transform) override;

	//GetDataTableRow Function
	void BeginPlay_SetupItem(int ItemID);
	void Constructor_SetupItem(int SetupItemID);

	virtual void PlayerToInteractable_InputInteractPressed_Implementation() override;
	virtual void PlayerToInteractable_HighlightTrace_Implementation() override;

	virtual void PlayerToInteractable_CustomDepthFilterOn_Implementation() override;
	virtual void PlayerToInteractable_CustomDepthFilterOff_Implementation() override;

	//Hit Fucntions for the physics interaction audio
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	bool bCanAudioPhysicsTriggerHit = true;
	FTimerHandle HitTimerHandle;
	void StartPhysicsHitTimer();
	void ResetHitTimer();
	void ItemActor_DrawDebugSphere(FVector Location, float Radius, FColor Color, float Duration, bool bPersistentLines);
	USoundCue* SwitchAudioOnPhysMaterial(EPhysicalSurface PhysicalMaterial, int ImpactClassificationInt);
	void SetMassFromDataTable();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Actor Debug")
	bool bShowPhysicsImpactAudioDebugSpheres = true;
	
	void AddSelfToInventory();
	
	//Audio Functions
	UFUNCTION(BlueprintNativeEvent)
	void BPAudio_ItemPickupAudio();
	UFUNCTION(BlueprintNativeEvent)
	void BPAudio_ItemActorPhysicsImpact_Light();
	UFUNCTION(BlueprintNativeEvent)
	void BPAudio_ItemActorPhysicsImpact_Medium();
	UFUNCTION(BlueprintNativeEvent)
	void BPAudio_ItemActorPhysicsImpact_Heavy();

	UPROPERTY (EditAnywhere, BlueprintReadWrite, Category = "Bouyancy Component")
	UBuoyancyComponent* BuoyancyComponent;
	// Physics Interaction  Audi DataAsset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicsInteractionAudio - DataAsset")
	UPhysicsInteractionAudioDataAsset* PhysicsInteractionAudioDataAsset;
};

