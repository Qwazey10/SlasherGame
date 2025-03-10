// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

//Engine
#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"

// Included Interfaces
#include "Interfaces/BPI_PlayerToEnemy.h"
#include "Interfaces/BPI_PlayerToInteractable.h"

// Included Components
#include "ActorComponent/AC_AbilityComponent.h"
#include "ActorComponent/AC_ImGuiActorDebug.h"
#include "ActorComponent/AC_PrimaryContextMenuManager.h"

// Included Data
#include "ActorComponent/EquipmentComponent.h"
#include "ActorComponent/SaveLoadComponent.h"
#include "Actors/WeaponActor.h"
#include "DataAssets/PlayerDataAsset.h"

//Generated .h
#include "SlasherCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;
class UAC_AbilityComponent;


UCLASS(config=Game)
class ASlasherCharacter : public ACharacter, public IBPI_PlayerToEnemy, public IBPI_PlayerToInteractable
{
	GENERATED_BODY()


	/** Pawn mesh: 1st person view (arms; seen only by self) */
	//UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	//USkeletalMeshComponent* Mesh1P;


	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;




public:
	ASlasherCharacter();

protected:
	virtual void BeginPlay() override;

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	UStaticMeshComponent* PrimaryItemMesh;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Data Asset Reference")
	UPlayerDataAsset* PlayerDataAsset;


	//Component Declarations
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAC_ImGuiActorDebug* DebugActorComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAC_AbilityComponent* AbilityComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAC_PrimaryContextMenuManager* PrimaryContextMenuManager;
	UPROPERTY(EditAnywhere, BlueprintreadWrite)
	UEquipmentComponent* EquipmentComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USaveLoadComponent* SaveLoadComponent;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;


	//****************** Slasher Character Attributes ********************


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float CurrentExperience;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float ExperienceToNextLevel;

	//HP MP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Base_Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float FromEquipment_Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float CurrentMana = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Base_MaxMana = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float FromEquipment_Mana = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float MaxMana = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Base_Guard = 0.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Base_HP_Regeneration = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Base_MP_Regeneration = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Base_Guard_Regeneration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float FromEquipment_HP_Regeneration = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float FromEquipment_MP_Regeneration = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float FromEquipment_Guard_Regeneration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Total_HP_Regeneration = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Total_MP_Regeneration = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Total_Guard_Regeneration = 0.0f;

	//Damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Base_Damage = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Base_AttackSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Base_MagicDamageMod = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float FromEquipment_Damage = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float FromEquipment_AttackSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float FromEquipment_MagicDamageMod = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Total_Damage = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Total_AttackSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Total_MagicDamageMod = 0.0f;

	//Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Base_Strength = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Base_Stamina = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Base_Dexterity = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Base_Intelligence = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float FromEquipment_Strength = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float FromEquipment_Stamina = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float FromEquipment_Dexterity = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float FromEquipment_Intelligence = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Total_Strength = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Total_Stamina = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Total_Dexterity = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Total_Intelligence = 0.0f;

	//Defensive Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Base_Armor = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Base_Resist_Fire = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Base_Resist_Cold = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Base_Resist_Detrimental = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Base_Resist_Divine = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float FromEquipment_Armor = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float FromEquipment_Resist_Fire = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float FromEquipment_Resist_Cold = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float FromEquipment_Resist_Detrimental = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float FromEquipment_Resist_Divine = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Total_Armor = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Total_Resist_Fire = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Total_Resist_Cold = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Total_Resist_Detrimental = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	float Total_Resist_Divine = 0.0f;

	//Combat Bools
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	bool bCanCast = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	bool bCanAttack = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	bool bCanJump = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	bool bCanBlock = true;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InteractTraceHitActorRef")
	AActor* InteractHitActor;

	//Interfaces

	IBPI_PlayerToEnemy* PlayerToEnemyInterface;

	IBPI_PlayerToInteractable* PlayerToInteractableInterface;

	//**Debug Codes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Booleans")
	bool bShowPlayerDebugMenu = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Booleans")
	bool bShowDebugItemTrace = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Booleans")
	bool bShowDebugEnemyTrace = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTables")
	UDataTable* ExperienceDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTables")
	UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTables")
	UDataTable* AbilityDataTable;


protected:
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	//Slasher Character Inputs

	//Directionals
	void OnPress_W();
	void OnPress_A();
	void OnPress_S();
	void OnPress_D();

	void OnRelease_W();
	void OnRelease_A();
	void OnRelease_S();
	void OnRelease_D();

	//Action Inputs
	void OnPress_Q();
	void OnPress_E();
	void OnPress_R();
	void OnPress_T();
	void OnPress_G();
	void OnPress_SHIFT();
	void OnPress_CTRL();
	void OnPress_SPACE();
	void OnPress_TAB();

	void OnRelease_Q();
	void OnRelease_E();
	void OnRelease_R();
	void OnRelease_T();
	void OnRelease_G();
	void OnRelease_SHIFT();
	void OnRelease_CTRL();
	void OnRelease_SPACE();
	void OnRelease_TAB();

	//BeginPlay Functions
	void BeginPlay_SetUpBaseVars();
	void BeginPlay_SetBaseAttributes();
	void BeginPlay_CreateInventoryWidgets();


	//General Functions

	void SlasherCharacter_TakeDamage(float DamageTaken);
	void DeathOfCharacter();


	//Player To Interactable Interface Functions 
	void InteractTrace();
	void InteractHighlightTrace();

	//Player ToEnemy Interface Functions
	void PlayerToEnemy_AttackTrace(EDamageType DamageType, float WeaponDamage);

	//Debug Functions
	void DebugItemTrace();

	//User Interface
	void ToggleInventoryWidget();


	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	//bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	//USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	void BeginPlay_SetLevel();
	void BeginPlay_SetEquipmentFromGIEquipment(); //Function that Loops Saved Equipment.
	void BeginPlay_RegisterEquipment();

	//Debug Functions
	void testFunc_SetBaseVars();
	void testFunc_SetupEquipmentPassives();
	void SetupEquipmentAttributes();
	void SwitchOnEquipPassive(EOnEquipPassive PassiveEffect);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug Booleans")
	bool ShowCharacterDebugMessages = false;

	void DebugCharacterPrintString(const FColor StringColor, const FString& String) const;
	void DebugCharacterPrintString_Error(const FString& String) const; //Generate 

	//Add Item To Inventory
	void RemoveItemFromInventory(int ItemIDToRemove);
	void AddItemToInventory(int ItemIDToAdd);

	//Equipment Functions
	void EquipItemID(int EquippedItemID); //Debug Function For Now - 


	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;


	// Function to update the capsule height during the timeline
	UFUNCTION()
	void SetCrouchHeight(float Alpha);

	// Function to handle timeline finished event
	UFUNCTION()
	void OnCrouchFinished() const;

	void FootStepLeft();
	void FootStepRight();

	void FootStepAudioLineTrace(int FootIndex);
	void PlayFootStepSoundAtLocation(FVector Location, USoundBase* SoundToPlay);

	//Footstep Audio 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Locomotion")
	bool bIsSprinting;

	//Debug Sprint Var That Toggles Boosted Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Locomotion")
	bool bDebug_DevSprint = true;

	void StartSprint();
	void EndSprint();

	UPROPERTY()
	UTimelineComponent* CrouchTimeline;

	void JumpPressWhileSwimming();
	UPROPERTY()
	bool bSpaceBarPressed = false;

	//Combat Functions
	void OnAttack();
	bool bIsAttacking = false;
	void AnimNotify_AttackWindowStart();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);


	/*
	 *  Rotating Mesh Menu System Vars
	 */

	void RotatingMenuItem_SetBaseRotation(float Rotation);

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	UStaticMeshComponent* RotatingMenuItemStaticMesh;
};
