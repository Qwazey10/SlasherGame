// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/SlasherChrAnimInstance.h"
#include "Character/SlasherCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


USlasherChrAnimInstance::USlasherChrAnimInstance()
{
	bChrAnimInst_Debug = false;


	ChrAnimInst_Speed = 0.0f;
	bChrAnimInst_IsSwimming = false;
	bChrAnimInst_IsInAir = false;
	bChrAnimInst_IsMoving = false;
	bChrAnimInst_IsSprinting = false;
	bChrAnimInst_IsJumping = false;
	EnumChrAnimInst_MovementMode = MOVE_None;
}

void USlasherChrAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	AActor* OwningActor = GetOwningActor();
	if (OwningActor != nullptr)
	{
		if (OwningActor->ActorHasTag(FName("Player")))
		{
			ASlasherCharacter* PlayerCharacter = Cast<ASlasherCharacter>(OwningActor);
			if (PlayerCharacter != nullptr)
			{
				ChrAnimInst_Speed = PlayerCharacter->GetCharacterMovement()->Velocity.Size();

				bChrAnimInst_IsMoving = ChrAnimInst_Speed > 1.0f; // Measure Animation
				bChrAnimInst_IsSprinting = PlayerCharacter->bIsSprinting;
				bChrAnimInst_IsJumping = PlayerCharacter->GetCharacterMovement()->IsFalling();
				// Set IsSprinting from Pawn.
				EnumChrAnimInst_MovementMode = PlayerCharacter->GetCharacterMovement()->MovementMode;

				if (bChrAnimInst_Debug)
				{
					if (GEngine)
					{
						FString TestString = FString::Printf(
							TEXT("Character Speed From Anim Graph -- %f"), ChrAnimInst_Speed);
						FString TestString2 = FString::Printf(
							TEXT("Anim Bool IsMovingBoolean -- %d"), bChrAnimInst_IsMoving);
						FString TestString3 = FString::Printf(
							TEXT("Anim Bool IsSprinting? -- %d"), bChrAnimInst_IsSprinting);
						FString TestString4 = FString::Printf(
							TEXT("Anim Bool IsFalling? -- %d"), bChrAnimInst_IsJumping);

						GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, TestString);
						GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, TestString2);
						GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, TestString3);
						GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, TestString4);
					}
				}
			}
		}
	}
}
