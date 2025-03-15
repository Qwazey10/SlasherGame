// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"

#include "Enemy/EnemyBaseAIController.h"
#include "GlobalUtils.h"
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

	PrimaryEquipmentMesh->AttachToComponent(BaseMesh, FAttachmentTransformRules::KeepRelativeTransform,TEXT("PrimaryEquipmentSocket"));
	SecondaryEquipmentMesh->AttachToComponent(BaseMesh, FAttachmentTransformRules::KeepRelativeTransform,TEXT("SecondaryEquipmentSocket"));

	//EnemyActorComponents
	AbilityComponent = CreateDefaultSubobject<UAC_AbilityComponent>(TEXT("AbilityComponent"));
	DamageComponent = CreateDefaultSubobject<UDamageComponent>(TEXT("DamageComponent"));
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	BeginPlay_SetDefensiveValuesInDamageComponent(); //Sets Defensive Stats In DamageComponent
	StartCheckStateChangeTimer();
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



// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}




/*
 * Death of Enemy
 */

void AEnemyBase::DeathOfOwner_Implementation()
{

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, TEXT("DeathOfOwner_Implementation INTERFACE FUNCTION CALLL"));
	StateChangeTimerHandle.Invalidate();
	GetWorldTimerManager().ClearTimer(StateChangeTimerHandle);

	GetWorldTimerManager().ClearAllTimersForObject(this);
	Destroy();
	
}

void AEnemyBase::BeginPlay_SetDefensiveValuesInDamageComponent()
{
	DamageComponent->DmgComponentArmor = EnemyBaseArmor;
	DamageComponent->DmgComponentResist_Fire = EnemyBaseResistFire;
	DamageComponent->DmgComponentResist_Cold = EnemyBaseResistCold;
	DamageComponent->DmgComponentResist_Detrimental = EnemyBaseResistDetrimental;
	DamageComponent->DmgComponentResist_Divine = EnemyBaseResistDivine;

	DamageComponent->bIsImmuneBurn = bIsImmuneBurn;
	DamageComponent->bIsImmuneFrost = bIsImmuneFrost;
	DamageComponent->bIsImmunePoison = bIsImmunePoison;
	DamageComponent->bIsImmuneBleed = bIsImmuneBleed;
}