// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"

#include "Enemy/EnemyBaseAIController.h"
#include "Structs/EnemyStruct.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add("Enemy");

	AIControllerClass = AEnemyBaseAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Set size for collision capsule
	//GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	BaseMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BaseMesh"));
	
	PrimaryEquipmentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PrimaryEquipmentMesh"));
	SecondaryEquipmentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondaryEquipmentMesh"));
	
	PrimaryEquipmentMesh->AttachToComponent(BaseMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("PrimaryEquipmentSocket"));
	SecondaryEquipmentMesh->AttachToComponent(BaseMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("SecondaryEquipmentSocket"));

	
	//Ability Component
	AbilityComponent = CreateDefaultSubobject<UAC_AbilityComponent>(TEXT("AbilityComponent"));
	
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AEnemyBase::StartCheckStateChangeTimer()
{
	const float Rand = FMath::RandRange(0.1f, 0.5f);
	
	GetWorld()->GetTimerManager().SetTimer(
 StateChangeTimerHandle,
 this,
 &AEnemyBase::CheckAIStateChange,
 Rand,
 true);
	
}

void AEnemyBase::CheckAIStateChange() const
{
	
	switch (CurrentState)
	
	{
	case EEnemyAIAgentState::None:
		{

			
			break;
		}
	case EEnemyAIAgentState::Idle:
		{

			
			break;
		}
	case EEnemyAIAgentState::Wonder:
		{
			
			
			break;
		}
	case EEnemyAIAgentState::Chase:
		{

			
			break;
		}
	case EEnemyAIAgentState::Attacking:
		{

			
			break;
		}
	case EEnemyAIAgentState::Ability:
		{

			
			break;
		}
	case EEnemyAIAgentState::Flee:
		{

			
			break;
		}

	}
}



void AEnemyBase::KillEnemyBase()
{
	
	//Destroy Actor
	
	StateChangeTimerHandle.Invalidate();
	GetWorldTimerManager().ClearTimer(StateChangeTimerHandle);

	GetWorldTimerManager().ClearAllTimersForObject(this);
	Destroy();
	
}
	
	


// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AEnemyBase::PlayerToEnemyInterface_Attack_Implementation(float Damage)
{
	
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black,"AttackInterface Call Received"+FString::FromInt(Damage));
	
}

void AEnemyBase::DamageTaken(float DamageAmount, AActor* DamageInstigator, EDamageType DamageType)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(DamageAmount));
}

//DebugCodeExcluder
//#if UE_BUILD_DEVELOPMENT || UE_BUILD_DEBUG
// Code specific to the Development or Debug build
//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, TEXT("CheckAIStateChange"));
//UE_LOG(LogTemp, Log, TEXT("This is a Development or Debug build."));
//#endif
