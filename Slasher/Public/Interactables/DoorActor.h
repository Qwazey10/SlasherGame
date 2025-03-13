// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableBase.h"
#include "Interfaces/BPI_PlayerToEnemy.h"
#include "Interfaces/BPI_PlayerToInteractable.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "DoorActor.generated.h"

UCLASS()
class SLASHER_API ADoorActor : public AInteractableBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoorActor();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite) Getting Base Mesh From InteractableBase
	//UStaticMeshComponent* DoorMesh;

	//Unique Vars to Door Mechanics
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* DoorCurve_Float;

	FTimeline DoorTimeline; // Timeline Definition 

	FOnTimelineFloat UpdateTimelineCallback;
	FOnTimelineEvent FinishTimelineCallback;


	FRotator InitialDoorRotation;
	FRotator FinishedDoorRotation;

	UFUNCTION()
	void HandleTimelineUpdate(float Value);

	UFUNCTION()
	void HandleTimelineFinished();
	//BP Audio Events
	UFUNCTION(BlueprintNativeEvent)
	void BPAudioEvent_OpenDoor();
	UFUNCTION(BlueprintNativeEvent)
	void BPAudioEvent_CloseDoor();

	void DoorInteractTrigger();
	void OpenDoor();
	void CloseDoor();

	//Booleans to help gate trigger presses
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsOpen;

private:
	FTimerHandle CustomDepthFilterOff_TimerHandle;

	//UFUNCTION()
	//void SetCustomDepthFilter_On();
	//UFUNCTION()
	//void SetCustomDepthFilter_Off();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void PlayerToEnemyInterface_Attack_Implementation(AActor* InstigatingActor, float BaseWeaponDamage, EDamageType PrimaryDamageType,float PrimaryStatusAmt, EDamageType SecondaryDamageType, float SecondaryStatusAmt) override;

	virtual void PlayerToInteractable_InputInteractPressed_Implementation() override;
	virtual void PlayerToInteractable_HighlightTrace_Implementation() override;
	/*virtual void PlayerToInteractable_CustomDepthFilterOn_Implementation() override;
	virtual void PlayerToInteractable_CustomDepthFilterOff_Implementation() override;*/

	//
};
