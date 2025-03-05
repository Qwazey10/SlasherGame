// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Sound/SoundCue.h"
#include "PlayerDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SLASHER_API UPlayerDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

	//Base Attributes
	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Stats")
	float BaseHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Stats")
	float BaseMana;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Stats")
	float BaseDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Stats")
	float BaseStrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Stats")
	float BaseStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Stats")
	float BaseDexterity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Stats")
	float BaseIntelligence;

	//Base Attack Values
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Attack Values")
	float BaseAttackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Attack Values")
	float FireMagicMod;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Attack Values")
	float ColdMagicMod;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Attack Values")
	float HolyMagicMod;

	// Base Character Defense Values.
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Defenses")
	float BaseArmor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category= "Base Defenses")
	float BaseFireResist;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category= "Base Defenses");
	float BaseColdResist;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category= "Base Defenses");
	float BaseDetrimentalResist;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category= "Base Defenses");
	float BaseDivineResist;
	
	//Movement Vars
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Movement")
	float BaseMovementSpeed = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Movement")
	float MaxSpeed = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Movement")
	float UpwardSwimSpeedMultiplier = 3.0f;

	//Audio Damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Damage")
	USoundCue* HitAudio_00;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Damage")
	USoundCue* HitAudio_01;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Damage")
	USoundCue* HitAudio_02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Damage")
	USoundCue* HitAudio_Stun;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Damage")
	USoundCue* HitAudio_Fall;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Damage")
	USoundCue* HitAudio_CriticalHit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Damage")
	USoundCue* HitAudio_Hurt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Damage")
	USoundCue* HitAudio_Miss;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Damage")
	USoundAttenuation* HitAudio_SoundAttenuation;
	
	//FootStep Audio 
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundCue* FootStepLeft_Default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundCue* FootStepRight_Default;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundCue* FootStepLeft_Wood;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundCue* FootStepRight_Wood;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundCue* FootStepLeft_Stone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundCue* FootStepRight_Stone;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundCue* FootStepLeft_Metal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundCue* FootStepRight_Metal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundCue* FootStepLeft_Water;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundCue* FootStepRight_Water;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundCue* FootStepLeft_Glass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundCue* FootStepRight_Glass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundCue* FootStepLeft_Grass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundCue* FootStepRight_Grass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundCue* FootStepLeft_Slime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundCue* FootStepRight_Slime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundCue* FootStepLeft_Lava;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundCue* FootStepRight_Lava;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - FootSteps")
	USoundAttenuation* FootStep_SoundAttenuation;
	
	
	//Interact Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Interact Highlight Range")
	float TraceDistance;

	//CrouchData
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Crouch Data")
	float StandingHeight = 96.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Crouch Data")
	float CrouchHeight = 42.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Crouch Data")
	float CrouchMovementSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Crouch Data")
	float CrouchSpeed = 0.15f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Crouch Data")
	UCurveFloat* CrouchCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Sprint Data")
	float SprintSpeed = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Sprint Data")
	float DEV_SprintSpeed = 2000.0f ;

	//Animation Montages
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Animation Montages")
	UAnimMontage* NormalAttackMontage;	
};
