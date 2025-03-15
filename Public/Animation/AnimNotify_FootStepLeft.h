// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_FootStepLeft.generated.h"


/**
 * 
 */
UCLASS()
class SLASHER_API UAnimNotify_FootStepLeft : public UAnimNotify
{
	GENERATED_BODY()

public:
	// Called when the animation notifies
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
