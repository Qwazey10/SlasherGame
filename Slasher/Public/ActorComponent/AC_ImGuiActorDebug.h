// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "imgui.h"

#include "CoreMinimal.h"
#include "Interactables/ItemActor.h"
#include "Components/ActorComponent.h"
#include "AC_ImGuiActorDebug.generated.h"

class AEnemyBase;
class ASlasherCharacter;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLASHER_API UAC_ImGuiActorDebug : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_ImGuiActorDebug();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Item DataTable")
	UDataTable* ItemDataTable;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) //OwnerReference
	AActor* OwnerReference;
	
	UPROPERTY(EditDefaultsOnly, Category=ItemActorClassReference)
	TSubclassOf<class AItemActor> ItemClass;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:


	//ImGui Color Pallette
	
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	static void BeginPlay_GetOwnerReference();


	void EnemyDebugInteractTrace();

	//ImGui Debug Context functions 
	void DisplayDebug_PlayerCharacter(AActor* Owner);
	
	static void DisplayDebug_Enemy(FHitResult* HitResult);
	static void DisplayDebug_Item(FHitResult* HitResult);
	
	void UtilityFunctionWindow();
	void DisplayInventoryWindow();
	
	void DebugFunction_GrantExp(float AmtToAdd);
	void DebugDisplayInventory();

	//Travel Commands
	void TravelToLevel(FString LevelName);

	//Debug Character Animation Vars
	void DebugCharacterAnimation();
	
	
	void SpawnItem(int ItemID);
	void ImGui_DrawDebugSphere(UWorld* World, FVector Location, float Radius, FColor Color, float Duration, bool bPersistentLines);
	
};
