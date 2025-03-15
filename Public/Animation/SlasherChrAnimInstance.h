// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SlasherChrAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SLASHER_API USlasherChrAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	USlasherChrAnimInstance();

public:
	//Debug Animation Boolean
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool bChrAnimInst_Debug;

	//Player Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	float ChrAnimInst_Speed;

	//Bool is in air
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool bChrAnimInst_IsInAir;

	//bool is swimming
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool bChrAnimInst_IsSwimming;

	//Bool Moving
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool bChrAnimInst_IsMoving;

	//Bool Is Sprinting?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool bChrAnimInst_IsSprinting;

	//Bool is Falling or Is Jumping
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool bChrAnimInst_IsJumping;

	//MovementMode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TEnumAsByte<EMovementMode> EnumChrAnimInst_MovementMode;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
