// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_OpenDamageNotify.h"

#include "Character/SlasherCharacter.h"

void UAnimNotify_OpenDamageNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* Owner = MeshComp->GetOwner();

	if (MeshComp && MeshComp->GetOwner())
	{
		if (Owner->ActorHasTag(FName("Player")))
		{
			ASlasherCharacter* PlayerCharacter = Cast<ASlasherCharacter>(Owner);
			if (PlayerCharacter)
			{
				PlayerCharacter->AnimNotify_AttackWindowStart();
			}
		}
	}
}
