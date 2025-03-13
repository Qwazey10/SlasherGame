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


	
	switch (PrimaryDamageType)
	{
		
	case EDamageType::Null:
		{
			GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red,
				"GlobalUtils.cpp -- CalculateDamage -- PrimaryDamageType is Null, Add Damage Type to PrimaryItemDatabase");
			break;
		}

	case EDamageType::DirectDamage_Physical:
		{
			InteractableBaseHealth = BaseWeaponDamage * (InteractableBaseArmor / 100.0f) / 100.0f;
			if (InteractableBaseHealth <= 0)
			{
				DestroyInteractable();
			}
			break;
		}

	case EDamageType::DirectDamage_Fire:
		{
			InteractableBaseHealth = BaseWeaponDamage * (InteractableBaseFireResist / 100.0f) / 100.0f;
			if (InteractableBaseHealth <= 0)
			{
				DestroyInteractable();
			}
		}

	case EDamageType::DIRECTDAMAGE_Cold:
		{
			InteractableBaseHealth = BaseWeaponDamage * (InteractableBaseFireResist / 100.0f) / 100.0f;
			if (InteractableBaseHealth <= 0)
			{
				DestroyInteractable();
			}
		}

	case EDamageType::DIRECTDAMAGE_Divine:
		{
			InteractableBaseHealth = BaseWeaponDamage * (InteractableBaseFireResist / 100.0f) / 100.0f;
			if (InteractableBaseHealth <= 0)
			{
				DestroyInteractable();
			}
		}

	case EDamageType::DIRECTDAMAGE_DETRIMENTAL_Poison:
		{
			InteractableBasePoisonBuildup = PrimaryStatusAmt * (InteractableBaseDetrimentalResist / 100.0f) / 100.0f;
			if (InteractableBasePoisonBuildup >= 100)
			{
				StartPoisonEffect();
			}
		}

	case EDamageType::DIRECTDAMAGE_DETRIMENTAL_Bleed:
		{
			InteractableBaseBleedBuildup = PrimaryStatusAmt * (InteractableBaseArmor / 100.0f) / 100.0f;
			if (InteractableBaseHealth >= 100)
			{
				StartBleedingEffect();
			}
		}

	case EDamageType::DIRECTDAMAGE_DETRIMENTAL_Fire:
		{
			InteractableBaseBurnBuildup = PrimaryStatusAmt * (InteractableBaseFireResist / 100.0f) / 100.0f;
			if (InteractableBaseHealth >= 100)
			{
				DestroyInteractable();
			}
		}

	case EDamageType::DIRECTDAMAGE_DETRIMENTAL_Cold:
		{
			InteractableBaseFrostBuildup = PrimaryStatusAmt * (InteractableBaseColdResist / 100.0f) / 100.0f;
			if (InteractableBaseHealth >= 100)
			{
				DestroyInteractable();
			}
		}

	default:
		{
			break;
		}
	}
	////////////Secondary Damage////////////////
	switch (SecondaryDamageType)
	{
		default:
		{
			break;
		}
			
	case EDamageType::Null:
		{
			GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red,
				"GlobalUtils.cpp -- CalculateDamage -- PrimaryDamageType is Null, Add Damage Type to PrimaryItemDatabase");
			break;
		}

	case EDamageType::DirectDamage_Physical:
		{
			InteractableBaseHealth = SecondaryStatusAmt * (InteractableBaseArmor / 100.0f) / 100.0f;
			if (InteractableBaseHealth <= 0)
			{
				DestroyInteractable();
			}
			break;
		}

	case EDamageType::DirectDamage_Fire:
		{
			InteractableBaseHealth = SecondaryStatusAmt * (InteractableBaseFireResist / 100.0f) / 100.0f;
			if (InteractableBaseHealth <= 0)
			{
				DestroyInteractable();
			}
		}

	case EDamageType::DIRECTDAMAGE_Cold:
		{
			InteractableBaseHealth = SecondaryStatusAmt * (InteractableBaseColdResist / 100.0f) / 100.0f;
			if (InteractableBaseHealth <= 0)
			{
				DestroyInteractable();
			}
		}

	case EDamageType::DIRECTDAMAGE_Divine:
		{
			InteractableBaseHealth = SecondaryStatusAmt * (InteractableBaseDivineResist / 100.0f) / 100.0f;
			if (InteractableBaseHealth <= 0)
			{
				DestroyInteractable();
			}
		}

	case EDamageType::DIRECTDAMAGE_DETRIMENTAL_Poison:
		{
			if (bIsInteractableImmuneMagic)
			{
				GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red,"Interactable is Immune to Poison");
			}
			else
			{
				InteractableBasePoisonBuildup = SecondaryStatusAmt * (InteractableBaseDetrimentalResist / 100.0f) / 100.0f;
				if (InteractableBasePoisonBuildup >= 100)
				{
					StartPoisonEffect();
				}
			}
		}

	case EDamageType::DIRECTDAMAGE_DETRIMENTAL_Bleed:
		{
				if (bIsInteractableImmuneBleed)
				{
					GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red,
						"Interactable is Immune to Bleed");
				}
				else
				{
					InteractableBasePoisonBuildup = SecondaryStatusAmt * (InteractableBaseDetrimentalResist / 100.0f) / 100.0f;
					if (InteractableBasePoisonBuildup >= 100)
					{
						StartBleedingEffect();
					}
				}
		}

	case EDamageType::DIRECTDAMAGE_DETRIMENTAL_Fire:
		{
				if (bIsInteractableImmuneFire)
				{
					GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Orange,
						"Interactable is Immune to Fire");
				}
				else
				{
					InteractableBasePoisonBuildup = SecondaryStatusAmt * (InteractableBaseDetrimentalResist / 100.0f) / 100.0f;
					if (InteractableBasePoisonBuildup >= 100)
					{
						StartBurningEffect();
					}
				}
		}

	case EDamageType::DIRECTDAMAGE_DETRIMENTAL_Cold:
		{
				
				if (bIsInteractableImmuneCold)
				{
					GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Cyan,
						"Interactable is Immune to COLD");
				}
				else
				{
					InteractableBaseFrostBuildup = SecondaryStatusAmt * (InteractableBaseColdResist / 100.0f) / 100.0f;
					if (InteractableBaseFrostBuildup >= 100)
					{
						StartFrostEffect();
					}
				}
				
		}
	}
}




/*
 * Burning Functions
 */

void AInteractableBase::StartBurningEffect()
{
	GetWorldTimerManager().SetTimer(
		BurningEffectTimerHandle,
		this,
		&AInteractableBase::ApplyBurningDamage,
		BurningTimerTickRate,
		true);
}
void AInteractableBase::ApplyBurningDamage()
{
	++BurningEffectTimerCount;
	if (BurningEffectTimerCount <= BurningEffectTimerCountMax)
	{
		InteractableBaseHealth = InteractableBaseHealth - BurnDamageBase;
		if (InteractableBaseHealth <= 0)
		{
			DestroyInteractable();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, TEXT("ApplyBurningDamage"));
		}
	}
	if (BurningEffectTimerCount >= BurningEffectTimerCountMax)
	{
		StopBurningEffect();
	}
}
void AInteractableBase::StopBurningEffect()
{
	GetWorldTimerManager().ClearTimer(BurningEffectTimerHandle);
}

/*
 * Poison Effect
 */

void AInteractableBase::StartPoisonEffect()
{
	
	GetWorldTimerManager().SetTimer(
	PoisonEffectTimerHandle,
	this,
	&AInteractableBase::ApplyPoisonDamage,
	PoisonTimerTickRate,
	true);
	
}
void AInteractableBase::ApplyPoisonDamage()
{
	InteractableBaseHealth = InteractableBaseHealth - PoisonDamageBase;
	if (InteractableBaseHealth <= 0)
	{
		DestroyInteractable();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, TEXT("ApplyPoisonDamage"));
	}
	++PoisonEffectTimerCount;
	if (PoisonEffectTimerCount >= PoisonEffectTimerCountMax)
	{
		StopPoisonEffect();
		GetWorldTimerManager().ClearTimer(PoisonEffectTimerHandle);
	}
}
void AInteractableBase::StopPoisonEffect()
{
	GetWorldTimerManager().ClearTimer(PoisonEffectTimerHandle);
}

/*
 * Frost Effect
 */

void AInteractableBase::StartFrostEffect()
{
	GetWorldTimerManager().SetTimer(
	FrostEffectTimerHandle,
	this,
	&AInteractableBase::ApplyFrostDamage,
	FrostTimerTickRate,
	true);
}
void AInteractableBase::ApplyFrostDamage()
{
	
	InteractableBaseMesh->SetSimulatePhysics(false);
	++FrostEffectTimerCount;
	if (FrostEffectTimerCount >= FrostEffectTimerCountMax)
	{
		StopFrostEffect();
	}
	
}
void AInteractableBase::StopFrostEffect()
{
	
	InteractableBaseMesh->SetSimulatePhysics(true);
	GetWorldTimerManager().ClearTimer(PoisonEffectTimerHandle);
	FrostEffectTimerCount = 0;
	
}

/*
 * Bleeding Effect
 */
void AInteractableBase::StartBleedingEffect()
{
	GetWorldTimerManager().SetTimer(
	BleedingEffectTimerHandle,
	this,
	&AInteractableBase::ApplyBleedingDamage,
	BleedingTimerTickRate,
	true);
}

void AInteractableBase::ApplyBleedingDamage()
{
	InteractableBaseHealth = (InteractableBaseHealth * 0.95) - BleedingDamageBase;
	if (InteractableBaseHealth <= 0)
	{
		DestroyInteractable();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, TEXT("ApplyBleedingDamage"));
	}
	++BleedingEffectTimerCount;
	if (BleedingEffectTimerCount >=BleedingEffectTimerCountMax)
	{
		StopBleedingEffect();
		
	}
}

void AInteractableBase::StopBleedingEffect()
{
	GetWorldTimerManager().ClearTimer(BleedingEffectTimerHandle);
}


//Destroy Interactable Actor
void AInteractableBase::DestroyInteractable()
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