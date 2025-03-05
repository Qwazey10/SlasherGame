// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_FootStepRight.generated.h"

/**
 * 
 */
UCLASS()
class SLASHER_API UAnimNotify_FootStepRight : public UAnimNotify
{
	GENERATED_BODY()

	public:
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
