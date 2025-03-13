// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Engine/DataAsset.h"
#include "Sound/SoundCue.h"
#include "PhysicsInteractionAudioDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SLASHER_API UPhysicsInteractionAudioDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	
	//Item Status Niagara
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Status Niagara")
	UNiagaraSystem* ItemStatusNiagara_Burning;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Status Niagara")
	UNiagaraSystem* ItemStatusNiagara_Poison;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Status Niagara")
	UNiagaraSystem* ItemStatusNiagara_Frost;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Status Niagara")
	UNiagaraSystem* ItemStatusNiagara_Bleeding;
	

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseItemAudio")
	USoundCue* BaseItemAudio_Pickup;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseItemAudio")
	USoundCue* BaseItemAudio_Destroy;
	//Default Impact Audio -- Light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType0 -- Impact Audio - Default")
	USoundCue* PhysicsImpact_Default_Light_00;

	//Default Impact Audio -- Medium
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType0 -- Impact Audio - Default")
	USoundCue* PhysicsImpact_Default_Medium_00;

	//Default Impact Audio - Heavy 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType0 -- Impact Audio - Default")
	USoundCue* PhysicsImpact_Default_Heavy_00;


	//Wood Impact Audio -- Light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType1 -- Impact Audio - Wood")
	USoundCue* PhysicsImpact_Wood_Light_00;

	//Wood Impact Audio -- Medium
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType1 -- Impact Audio - Wood")
	USoundCue* PhysicsImpact_Wood_Medium_00;

	//Wood Impact Audio - Heavy 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType1 -- Impact Audio - Wood")
	USoundCue* PhysicsImpact_Wood_Heavy_00;


	//Stone Impact Audio -- Light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType2 -- Impact Audio - Stone")
	USoundCue* PhysicsImpact_Stone_Light_00;

	// Stone Impact Audio -- Medium
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType2 -- Impact Audio - Stone")
	USoundCue* PhysicsImpact_Stone_Medium_00;

	//Stone Impact Audio -- Heavy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType2 -- Impact Audio - Stone")
	USoundCue* PhysicsImpact_Stone_Heavy_00;


	//Metal Impact Audio -- Light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType3 -- Impact Audio - Metal")
	USoundCue* PhysicsImpact_Metal_Light_00;

	//Metal Impact Audio -- Medium
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType3 -- Impact Audio - Metal")
	USoundCue* PhysicsImpact_Metal_Medium_00;

	//Metal Impact Audio -- Heavy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType3 -- Impact Audio - Metal")
	USoundCue* PhysicsImpact_Metal_Heavy_00;


	//Water Impact Audio -- Light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType4 -- Impact Audio - Water")
	USoundCue* PhysicsImpact_Water_Light_00;

	//Water Impact Audio -- Medium
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType4 -- Impact Audio - Water")
	USoundCue* PhysicsImpact_Water_Medium_00;

	//Water Impact Audio -- Heavy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType4 -- Impact Audio - Water")
	USoundCue* PhysicsImpact_Water_Heavy_00;


	//Glass Impact Audio - Light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType5 -- Impact Audio - Glass")
	USoundCue* PhysicsImpact_Glass_Light_00;

	//Glass Impact Audio - Medium
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType5 -- Impact Audio - Glass")
	USoundCue* PhysicsImpact_Glass_Medium_00;

	//Glass Impact Audio - Heavy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType5 -- Impact Audio - Glass")
	USoundCue* PhysicsImpact_Glass_Heavy_00;


	//Grass Impact Audio - Light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType6 -- Impact Audio - Glass")
	USoundCue* PhysicsImpact_Grass_Light_00;

	//Glass Impact Audio - Medium
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType6 -- Impact Audio - Glass")
	USoundCue* PhysicsImpact_Grass_Medium_00;

	//Glass Impact Audio - Heavy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType6 -- Impact Audio - Glass")
	USoundCue* PhysicsImpact_Grass_Heavy_00;


	//Slime Impact Audio - Light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType7 -- Impact Audio - Slime")
	USoundCue* PhysicsImpact_Slime_Light_00;

	//Slime Impact Audio - Medium
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType7 -- Impact Audio - Slime")
	USoundCue* PhysicsImpact_Slime_Medium_00;

	//Slime Impact Audio - Heavy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType7 -- Impact Audio  - Slime")
	USoundCue* PhysicsImpact_Slime_Heavy_00;


	//Lava Impact Audio - Light
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType8 -- Impact Audio - Lava")
	USoundCue* PhysicsImpact_Lava_Light_00;

	//Lava Impact Audio - Medium
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType8 -- Impact Audio - Lava")
	USoundCue* PhysicsImpact_Lava_Medium_00;

	//Lava Impact Audio - Heavy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SurfaceType8 -- Impact Audio - Lava")
	USoundCue* PhysicsImpact_Lava_Heavy_00;


	//Audio Attenuation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio - Attenuation")
	USoundAttenuation* PhysicsImpact_SoundAttenuation_Light;

	//Audio Attenuation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio - Attenuation")
	USoundAttenuation* PhysicsImpact_SoundAttenuation_Medium;

	//Audio Attenuation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio - Attenuation")
	USoundAttenuation* PhysicsImpact_SoundAttenuation_Heavy;
};
