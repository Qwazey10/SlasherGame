// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Sound/SoundCue.h"
#include "EnemyStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct SLASHER_API FEnemyStruct: public FTableRowBase
{
public:

	GENERATED_BODY()

	//Appearance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skeletal Mesh")
	USkeletalMesh* EnemyMesh = nullptr;

	//Animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation BP")
	TSubclassOf<UAnimInstance> AnimationBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Description")
	FString EnemyName = "EnemyName";
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Stats")
	float Health = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Stats")
	float HealthRegen = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Stats")
	float Mana = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Stats")
	float ManaRegen = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Stats")
	float BaseDamage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Stats")
	float BaseStrength = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Stats")
	float BaseStamina = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Stats")
	float BaseDexterity = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Stats")
	float BaseIntelligence = 0;

	
	//Base Attack Values
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Attack Values")
	float BaseAttackSpeed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Attack Values")
	float FireMagicMod = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Attack Values")
	float ColdMagicMod = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Attack Values")
	float HolyMagicMod = 0;

	// Base Character Defense Values.
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Defenses")
	float Armor = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category= "Base Defenses")
	float FireResist = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category= "Base Defenses");
	float ColdResist = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category= "Base Defenses");
	float DetrimentalResist = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category= "Base Defenses");
	float DivineResist = 0;
	
	//Movement Vars
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Movement")
	float BaseMovementSpeed = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Base Movement")
	float MaxSpeed = 0;

	//Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Idle")
	USoundCue* IdleSound = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Idle")
	USoundCue* Footstep_Left = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Idle")
	USoundCue* Footstep_Right = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Damage")
	USoundCue* HitAudio_00 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Damage")
	USoundCue* HitAudio_01 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Damage")
	USoundCue* HitAudio_02 = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Damage")
	USoundCue* HitAudio_Stun = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Damage")
	USoundCue* HitAudio_Fall = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Damage")
	USoundCue* HitAudio_CriticalHit = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Damage")
	USoundCue* HitAudio_Hurt = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Damage")
	USoundCue* HitAudio_Miss = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Audio - Damage")
	USoundAttenuation* HitAudio_SoundAttenuation = nullptr;
	

	
	FEnemyStruct();
	~FEnemyStruct();
};
