// Fill out your copyright notice in the Description page of Project Settings.

//Engine
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include "ActorComponent/AC_AbilityComponent.h"
#include "Modes/SlasherGameInstance.h"




//Include Actors
#include "Enemy/EnemyBase.h"
#include "Character/SlasherCharacter.h"




// Sets default values for this component's properties
UAC_AbilityComponent::UAC_AbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


FHitResult UAC_AbilityComponent::Utility_LineTrace(FVector StartLoc, FVector EndLoc, EDrawDebugTrace::Type TraceType,
	float TraceDistance, float DrawTime) const
{
	FHitResult Hit;
	TArray<AActor*> ActorsToIgnore;
	
	const bool bHit = UKismetSystemLibrary::LineTraceSingle(
		this,
		StartLoc,
		EndLoc,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		ActorsToIgnore,
		TraceType, // Trace Types for Line Trace --  None, For Duration , ForOneFrame, Persistant 
		Hit,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		DrawTime
		);
	
	if (bHit)
	{
		return Hit;
	}
	else
	{
		return FHitResult();
	}
}
	 


// Called when the game starts
void UAC_AbilityComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner(); //
	if (Owner->ActorHasTag(FName("Player")))
	{
		ASlasherCharacter* PlayerCharacter = Cast<ASlasherCharacter>(Owner);
	}
	if (Owner->ActorHasTag(FName("Enemy")))
	{
		AEnemyBase* EnemyCharacter = Cast<AEnemyBase>((Owner));
	}
	
	// ...
	
}


// Called every frame
void UAC_AbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}



void UAC_AbilityComponent::ExecuteAbilityID(
		int AbilityID,
		EAbilityType InputAbilityType,
		float InputRange,
		float InputCooldown,
		float InputDuration,
		float TickRate,
		float AbilityMod00,
		float AbilityMod01,
		float AbilityMod02,
		float AbilityMod03)
{
	//Start Ability Switch
	switch (AbilityID)
	{
		default:
			break;
		//Generic Abilities
		case 0:
			{
				UE_LOG(LogTemp, Verbose, TEXT("Ability ID 0 Triggered"))
				return;
			}
			
		
		case 1:
			{
				Grant_Experience_AbilityID_001(AbilityMod00);
				return;
			}
		case 2:
			{
				UE_LOG(LogTemp, Warning, TEXT("%d"), AbilityID);
				return;
			}
		case 3:
			{
				if (InputAbilityType == EAbilityType::Passive)
				{
					UE_LOG(LogTemp, Warning, TEXT(" Execute Ability ID%d"), AbilityID);
					break;
				}
				break;
			}
		
		
	}
}


//GetDataTable Row


void UAC_AbilityComponent::Grant_Experience_AbilityID_001(float AmtOfEXPToAdd)
{
	AActor* LocalOwner = GetOwner();
	if (LocalOwner->ActorHasTag(FName("Player")))
	{
		UWorld* World =  LocalOwner->GetWorld();
		if (World)
		{
			USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(World->GetGameInstance());
			SlasherGI->GI_CurrentExperience += AmtOfEXPToAdd;
			ASlasherCharacter* PlayerCharacter = Cast<ASlasherCharacter>(LocalOwner);
			if (PlayerCharacter)
			{
				PlayerCharacter->BeginPlay_SetLevel();
			}
		}

		
	}
	if (LocalOwner->ActorHasTag("Enemy"))
	{
		AEnemyBase* EnemyCharacter = Cast<AEnemyBase>(LocalOwner);
		UE_LOG(LogTemp, Warning, TEXT("AC_AbilityComponent -- Ability ID 001 Called on an Enemy %s -- No EXP to ADD"), *GetOwner()->GetName());
	}
}


void UAC_AbilityComponent::SetMovementSpeed(float WalkSpeedSet)
{
	AActor* Owner = GetOwner();
	if (Owner->ActorHasTag(FName("Player")))
	{
		ASlasherCharacter* PlayerCharacter = Cast<ASlasherCharacter>(Owner);
		PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeedSet;
		
	}
	if (Owner->ActorHasTag("Enemy"))
	{
		AEnemyBase* EnemyCharacter = Cast<AEnemyBase>(Owner);
		EnemyCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeedSet;
	}
}

