// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/InteractableBase.h"

#include "Interfaces/BPI_PlayerToEnemy.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInteractableBase::AInteractableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractableBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractableBaseMesh"));
	InteractableBaseMesh->SetSimulatePhysics(false);
	RootComponent = InteractableBaseMesh;

	DamageComponent = CreateDefaultSubobject<UDamageComponent>(TEXT("DamageComponent"));
	

}

// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableBase::PlayerToInteractable_InputInteractPressed_Implementation()
{
	IBPI_PlayerToInteractable::PlayerToInteractable_InputInteractPressed_Implementation();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "HELLO FROM INTERACTABLE BASE!");
}

void AInteractableBase::PlayerToInteractable_HighlightTrace_Implementation()
{
	IBPI_PlayerToInteractable::PlayerToInteractable_HighlightTrace_Implementation();
}

//Interactable Highlight Trace Functions
void AInteractableBase::PlayerToInteractable_CustomDepthFilterOn_Implementation()
{
	IBPI_PlayerToInteractable::PlayerToInteractable_CustomDepthFilterOn_Implementation();
	InteractableBaseMesh->SetRenderCustomDepth(true);
	InteractableBaseMesh->SetCustomDepthStencilValue(1);
}

void AInteractableBase::PlayerToInteractable_CustomDepthFilterOff_Implementation()
{
	IBPI_PlayerToInteractable::PlayerToInteractable_CustomDepthFilterOff_Implementation();
	InteractableBaseMesh->SetRenderCustomDepth(false);
	InteractableBaseMesh->SetCustomDepthStencilValue(0);
}


/*
 * Combat Functions 
 */

void AInteractableBase::PlayerToEnemyInterface_Attack_Implementation(AActor* InstigatingActor, float BaseWeaponDamage,
	EDamageType PrimaryDamageType, float PrimaryStatusAmt, EDamageType SecondaryDamageType, float SecondaryStatusAmt)
{
	IBPI_PlayerToEnemy::PlayerToEnemyInterface_Attack_Implementation(InstigatingActor, BaseWeaponDamage,
																	 PrimaryDamageType, PrimaryStatusAmt,
																	 SecondaryDamageType,
																	 SecondaryStatusAmt);

	DamageComponent->ApplyDamage(InstigatingActor,BaseWeaponDamage,PrimaryDamageType, PrimaryStatusAmt, SecondaryDamageType, SecondaryStatusAmt);
}


//Destroy Interactable Actor
//Function is called in the DamageComponent when CurrentHealth is zero or below. 
void AInteractableBase::DeathOfOwner_Implementation()
{
		
	UGameplayStatics::PlaySoundAtLocation(
		this,
		PhysicsInteractionAudioDataAsset->BaseItemAudio_Destroy,
		GetActorLocation(),
		GetActorRotation(),
		FMath::FRandRange(0.5f, 1.0f),
		FMath::FRandRange(0.7f, 1.0f),0,
		PhysicsInteractionAudioDataAsset->PhysicsImpact_SoundAttenuation_Light);
	
	Destroy();
	
}

void AInteractableBase::DmgInterfaceApplyEffectCosmeticBurning_Implementation()
{
	//tehe
}

void AInteractableBase::DmgInterfaceApplyEffectCosmeticBleeding_Implementation()
{
	//tehe
}

void AInteractableBase::DmgInterfaceApplyEffectCosmeticPoison_Implementation()
{
	//tehe
}

void AInteractableBase::DmgInterfaceApplyEffectCosmeticFrost_Implementation()
{
	//tehe
}
