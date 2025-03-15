// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/DamageComponent.h"
#include "GlobalEnums.h"
#include "GlobalUtils.h"
#include "Enemy/EnemyBase.h"
#include "Character/SlasherCharacter.h"


// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	GetDefenseVarsFromOwner();
	
}


// Called every frame
void UDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UDamageComponent::GetDefenseVarsFromOwner()
{
	if (IsValid(GetOwner()))
	{
		if (GetOwner()->ActorHasTag("Player"))
		{
			ASlasherCharacter* SlasherCharacter = Cast<ASlasherCharacter>(GetOwner());
			
			DmgComponentArmor = SlasherCharacter->Total_Armor;
			DmgComponentResist_Fire = SlasherCharacter->Total_Resist_Fire;
			DmgComponentResist_Cold = SlasherCharacter->Total_Resist_Cold;
			DmgComponentResist_Detrimental = SlasherCharacter->Total_Resist_Detrimental;
			DmgComponentResist_Divine = SlasherCharacter->Total_Resist_Divine;
		}
		
		if (GetOwner()->ActorHasTag("Enemy"))
		{
			AEnemyBase* EnemyBaseActor = Cast<AEnemyBase>(GetOwner());
			
			DmgComponentArmor = EnemyBaseActor->EnemyBaseArmor;
			DmgComponentResist_Fire = EnemyBaseActor->EnemyBaseResistFire;
			DmgComponentResist_Cold = EnemyBaseActor->EnemyBaseResistCold;
			DmgComponentResist_Detrimental = EnemyBaseActor->EnemyBaseResistDetrimental;
			DmgComponentResist_Divine = EnemyBaseActor->EnemyBaseResistDivine;
		}
		
		if (GetOwner()->ActorHasTag("Interactable"))
		{
			AInteractableBase* InteractableBaseActor = Cast<AInteractableBase>(GetOwner());

			DmgComponentArmor = InteractableBaseActor->InteractableBaseArmor;
			DmgComponentResist_Fire = InteractableBaseActor->InteractableBaseFireResist;
			DmgComponentResist_Cold = InteractableBaseActor->InteractableBaseColdResist;
			DmgComponentResist_Detrimental = InteractableBaseActor->InteractableBaseDetrimentalResist;
			DmgComponentResist_Divine = InteractableBaseActor->InteractableBaseDivineResist;
			
		}

	}


}

//Call The Death Interface Event on Owner
void UDamageComponent::CallDeathOfOwnerInterface()
{
	if (IsValid(GetOwner() && GetOwner->GetClass()->ImplementsInterface(UBPI_DamageInterface::StaticClass())))
	{
		IBPI_DamageInterface* InterfaceCallActor = Cast<IBPI_DamageInterface>(GetOwner());
		InterfaceCallActor->Execute_DeathOfOwner(GetOwner());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red,
			"DamageComponent::CallDeathOfOwnerInterface -- GetOwner() is not valid Or DOES NOT IMPLEMENT DAMAGE INTERFACE");
	}
}

void UDamageComponent::DealDamage(AActor* InstigatingActor, float BaseWeaponDamage,
	EDamageType PrimaryDamageType, float PrimaryStatusAmt, EDamageType SecondaryDamageType, float SecondaryStatusAmt)
{
	
	ApplyDamage(InstigatingActor, BaseWeaponDamage, PrimaryDamageType, PrimaryStatusAmt);
	ApplyDamage(InstigatingActor, BaseWeaponDamage, SecondaryDamageType, SecondaryStatusAmt);
	
}

void UDamageComponent::ApplyDamage(AActor* InstigatingActor, float BaseWeaponDamage,
	EDamageType DamageType, float StatusAmt)
{
	switch (DamageType)
	{
		
	case EDamageType::Null:
		{
			GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red,
				"GlobalUtils.cpp -- CalculateDamage -- PrimaryDamageType is Null, Add Damage Type to PrimaryItemDatabase");
			break;
		}

	case EDamageType::DirectDamage_Physical:
		{
			CurrentHealth = CalculateBaseDamage(BaseWeaponDamage, DmgComponentArmor);
			if (CurrentHealth <= 0)
			{
				CallDeathOfOwnerInterface();
			}
			break;
		}

	case EDamageType::DirectDamage_Fire:
		{
			CurrentHealth = CalculateBaseDamage(BaseWeaponDamage, DmgComponentResist_Fire);
			if (CurrentHealth <= 0)
			{
				CallDeathOfOwnerInterface();
			}
		}

	case EDamageType::DIRECTDAMAGE_Cold:
		{
			CurrentHealth = CalculateBaseDamage(BaseWeaponDamage, DmgComponentResist_Cold);
			if (CurrentHealth <= 0)
			{
				CallDeathOfOwnerInterface();
			}
		}

	case EDamageType::DIRECTDAMAGE_Divine:
		{
			CurrentHealth = CalculateBaseDamage(BaseWeaponDamage, DmgComponentResist_Divine);
			if (CurrentHealth <= 0)
			{
				CallDeathOfOwnerInterface();
			}
		}

	case EDamageType::DIRECTDAMAGE_DETRIMENTAL_Poison:
		{
			if (!bIsImmunePoison)
			{
				BasePoisonBuildup = CalculateStatusDamage(StatusAmt, DmgComponentResist_Detrimental);
				if (BasePoisonBuildup >= 100)
				{
					StartPoisonEffect();
				}
			}

		}

	case EDamageType::DIRECTDAMAGE_DETRIMENTAL_Bleed:
		{
			if (bIsImmuneBleed)
			{
				GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red,
					"Interactable is Immune to Bleed");
			}
			else
			{
				BaseBleedBuildup = CalculateStatusDamage(StatusAmt, DmgComponentResist_Detrimental);
				if (BaseBleedBuildup >= 100)
				{
					StartBleedingEffect();
				}
			}
		}

	case EDamageType::DIRECTDAMAGE_DETRIMENTAL_Fire:
		{
			if (bIsImmuneBurn)
			{
				FString ErrorString = "DamageComponent.cpp -- ApplyDamage() -- Target is Immune to Burn";
				GlobalUtils::PrintErrorString(GetWorld(),ErrorString);
			}
			else
			{
				BaseBurnBuildup = CalculateStatusDamage(StatusAmt, DmgComponentResist_Fire);
				if (BaseBurnBuildup >= 100)
				{
					StartBurningEffect();
				}
			}
			
			if (BaseBurnBuildup >= 100)
			{
				StartBurningEffect();
			}
		}

	case EDamageType::DIRECTDAMAGE_DETRIMENTAL_Cold:
		{
			BaseFrostBuildup = StatusAmt * (DmgComponentResist_Cold / 100.0f) / 100.0f;
			if (BaseFrostBuildup >= 100)
			{
				StartFrostEffect();
			}
		}

	default:
		{
			break;
		}
	}
}

float UDamageComponent::CalculateStatusDamage(const float StatusAmt, const float StatusDefense)
{
	float StatusDamage = StatusAmt * (StatusDefense / 100.0f);
	return StatusDamage;
}

float UDamageComponent::CalculateBaseDamage(const float BaseDamage, const float DamageTypeResist)
{
	float Damage = BaseDamage * (DamageTypeResist / 100.0f);
	return Damage;
}


/*
 * Burning Functions
 */

void UDamageComponent::StartBurningEffect()
{
	GetOwner()->GetWorldTimerManager().SetTimer(
		BurningEffectTimerHandle,
		this,
		&UDamageComponent::ApplyBurningDamage,
		BurningTimerTickRate,
		true);

	BaseBurnBuildup = 0;
	DmgInterfaceApplyEffectCosmeticBurning(); // Start cosmetic burning effect if applicable.
}
void UDamageComponent::ApplyBurningDamage()
{
	++BurningEffectTimerCount;
	if (BurningEffectTimerCount <= BurningEffectTimerCountMax)
	{
		CurrentHealth = CurrentHealth - BurnDamageBase;
		if (CurrentHealth <= 0)
		{
			if (IsValid(GetOwner() && GetOwner->GetClass()->ImplementsInterface(UBPI_DamageInterface::StaticClass())))
			{
				IBPI_DamageInterface* InterfaceCallActor = Cast<IBPI_DamageInterface>(GetOwner());
				InterfaceCallActor->Execute_DeathOfOwner(GetOwner());
			}
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
void UDamageComponent::StopBurningEffect()
{
	DmgInterfaceApplyEffectCosmeticBurning_End(); // End cosmetic burning effect if applicable.
	GetOwner()->GetWorldTimerManager().ClearTimer(BurningEffectTimerHandle);
}

/*
 * Poison Effect
 */

void UDamageComponent::StartPoisonEffect()
{
	
	GetOwner()->GetWorldTimerManager().SetTimer(
	PoisonEffectTimerHandle,
	this,
	&UDamageComponent::ApplyPoisonDamage,
	PoisonTimerTickRate,
	true);

	BasePoisonBuildup = 0;
	CallDmgInterfaceApplyEffectCosmeticPoison(); // Start cosmetic poison effect if applicable.
	
}
void UDamageComponent::ApplyPoisonDamage()
{
	DmgInterfaceApplyEffectCosmeticPoison(); // Start cosmetic poison effect if applicable.
	CurrentHealth = CurrentHealth - PoisonDamageBase;
	if (CurrentHealth <= 0)
	{
		if (IsValid(GetOwner() && GetOwner->GetClass()->ImplementsInterface(UBPI_DamageInterface::StaticClass())))
		{
			IBPI_DamageInterface* InterfaceCallActor = Cast<IBPI_DamageInterface>(GetOwner());
			InterfaceCallActor->Execute_DeathOfOwner(GetOwner());
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, TEXT("ApplyPoisonDamage"));
	}
	++PoisonEffectTimerCount;
	if (PoisonEffectTimerCount >= PoisonEffectTimerCountMax)
	{
		StopPoisonEffect();
		GetOwner()->GetWorldTimerManager().ClearTimer(PoisonEffectTimerHandle);
	}
}
void UDamageComponent::StopPoisonEffect()
{
	DmgInterfaceApplyEffectCosmeticPoison_End(); // End cosmetic poison effect if applicable.
	PoisonEffectTimerCount = 0;
	GetOwner()->GetWorldTimerManager().ClearTimer(PoisonEffectTimerHandle);
}

/*
 * Frost Effect
 */

void UDamageComponent::StartFrostEffect()
{
	GetOwner()->GetWorldTimerManager().SetTimer(
	FrostEffectTimerHandle,
	this,
	&UDamageComponent::ApplyFrostDamage,
	FrostTimerTickRate,
	true);

	BaseFrostBuildup = 0;
	CallDmgInterfaceApplyEffectCosmeticFrost(); // Start cosmetic frost effect if applicable.
}
void UDamageComponent::ApplyFrostDamage()
{
	
	
	++FrostEffectTimerCount;
	if (FrostEffectTimerCount >= FrostEffectTimerCountMax)
	{
		StopFrostEffect();
	}
	
}
void UDamageComponent::StopFrostEffect()
{
	
	//GetMesh()->SetSimulatePhysics(true);
	DmgInterfaceApplyEffectCosmeticFrost_End(); // End cosmetic frost effect if applicable.
	GetOwner()->GetWorldTimerManager().ClearTimer(PoisonEffectTimerHandle);
	FrostEffectTimerCount = 0;
	
}

/*
 * Bleeding Effect
 */
void UDamageComponent::StartBleedingEffect()
{
	GetOwner()->GetWorldTimerManager().SetTimer(
	BleedingEffectTimerHandle,
	this,
	&UDamageComponent::ApplyBleedingDamage,
	BleedingTimerTickRate,
	true);

	BasePoisonBuildup = 0;
	DmgInterfaceApplyEffectCosmeticBleed(); // Start cosmetic bleeding effect if applicable. 
}

void UDamageComponent::ApplyBleedingDamage()
{
	if (bIsImmuneBleed)
	{
		GlobalUtils::PrintErrorString(GetWorld(), "Interactable is Immune to Bleed");
	}
	else
	{
		CurrentHealth = (CurrentHealth * 0.95) - BleedingDamageBase;
		if (CurrentHealth <= 0)
		{
			if (IsValid(GetOwner() && GetOwner->GetClass()->ImplementsInterface(UBPI_DamageInterface::StaticClass())))
			{
				IBPI_DamageInterface* InterfaceCallActor = Cast<IBPI_DamageInterface>(GetOwner());
				InterfaceCallActor->Execute_DeathOfOwner(GetOwner());
			}
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
}

void UDamageComponent::StopBleedingEffect()
{
	GetOwner()->GetWorldTimerManager().ClearTimer(BleedingEffectTimerHandle);
	BleedingEffectTimerCount = 0;
	DmgInterfaceApplyEffectCosmeticBleed_End();
}


// Call and END cosmetic burning. 
void UDamageComponent::CallDmgInterfaceApplyEffectCosmeticBurning()
{
	if (IsValid(GetOwner() && GetOwner->GetClass()->ImplementsInterface(UBPI_DamageInterface::StaticClass())))
	{
		IBPI_DamageInterface* InterfaceCallActor = Cast<IBPI_DamageInterface>(GetOwner());
		InterfaceCallActor->Execute_DmgInterfaceApplyEffectCosmeticBurning(GetOwner());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red,
	"DamageComponent::CallDeathOfOwnerInterface -- GetOwner() is not valid Or DOES NOT IMPLEMENT DAMAGE INTERFACE");
	}
}

void UDamageComponent::EndDmgInterfaceApplyEffectCosmeticBurning()
{
	if (IsValid(GetOwner() && GetOwner->GetClass()->ImplementsInterface(UBPI_DamageInterface::StaticClass())))
	{
		IBPI_DamageInterface* InterfaceCallActor = Cast<IBPI_DamageInterface>(GetOwner());
		InterfaceCallActor->Execute_DmgInterfaceApplyEffectCosmeticBurning_End(GetOwner());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red,
	"DamageComponent::CallDeathOfOwnerInterface -- GetOwner() is not valid Or DOES NOT IMPLEMENT DAMAGE INTERFACE");
	}
}

/*
 * Call End Effect Cosmetic //// Poison ///// 
 */


void UDamageComponent::CallDmgInterfaceApplyEffectCosmeticPoison()
{
	if (IsValid(GetOwner() && GetOwner->GetClass()->ImplementsInterface(UBPI_DamageInterface::StaticClass())))
	{
		IBPI_DamageInterface* InterfaceCallActor = Cast<IBPI_DamageInterface>(GetOwner());
		InterfaceCallActor->Execute_DmgInterfaceApplyEffectCosmeticPoison(GetOwner());
	}
	else
	{
		FString ErrorString = "DamageComponent::CallDeathOfOwnerInterface -- GetOwner() is not valid Or DOES NOT IMPLEMENT DAMAGE INTERFACE";
		GlobalUtils::PrintErrorString(GetWorld(), ErrorString);
	}
}

void UDamageComponent::EndDmgInterfaceApplyEffectCosmeticPoison()
{
	if (IsValid(GetOwner() && GetOwner->GetClass()->ImplementsInterface(UBPI_DamageInterface::StaticClass())))
	{
		IBPI_DamageInterface* InterfaceCallActor = Cast<IBPI_DamageInterface>(GetOwner());
		InterfaceCallActor->Execute_DmgInterfaceApplyEffectCosmeticPoison_End(GetOwner());
	}
	else
	{
		FString ErrorString = "DamageComponent::CallDeathOfOwnerInterface -- GetOwner() is not valid Or DOES NOT IMPLEMENT DAMAGE INTERFACE";
		GlobalUtils::PrintErrorString(GetWorld(), ErrorString);
	}
}



/*
 * Call End Effect Cosmetic BLEED EFFECT
 */
void UDamageComponent::CallDmgInterfaceApplyEffectCosmeticBleed()
{
	if (IsValid(GetOwner() && GetOwner->GetClass()->ImplementsInterface(UBPI_DamageInterface::StaticClass())))
	{
		IBPI_DamageInterface* InterfaceCallActor = Cast<IBPI_DamageInterface>(GetOwner());
		InterfaceCallActor->Execute_DmgInterfaceApplyEffectCosmeticBleed(GetOwner());
	}
	else
	{
		FString ErrorString = "DamageComponent::CallDeathOfOwnerInterface -- GetOwner() is not valid Or DOES NOT IMPLEMENT DAMAGE INTERFACE";
		GlobalUtils::PrintErrorString(GetWorld(), ErrorString);
	}
}

void UDamageComponent::EndDmgInterfaceApplyEffectCosmeticBleed()
{
	if (IsValid(GetOwner() && GetOwner->GetClass()->ImplementsInterface(UBPI_DamageInterface::StaticClass())))
	{
		IBPI_DamageInterface* InterfaceCallActor = Cast<IBPI_DamageInterface>(GetOwner());
		InterfaceCallActor->Execute_DmgInterfaceApplyEffectCosmeticBleed_End(GetOwner());
	}
	else
	{
		FString ErrorString = "DamageComponent::CallDeathOfOwnerInterface -- GetOwner() is not valid Or DOES NOT IMPLEMENT DAMAGE INTERFACE";
		GlobalUtils::PrintErrorString(GetWorld(), ErrorString);
	}
}

/*
 * Call and End Interface for FROST EFFECT.
 */
void UDamageComponent::CallDmgInterfaceApplyEffectCosmeticFrost()
{
	if (IsValid(GetOwner() && GetOwner->GetClass()->ImplementsInterface(UBPI_DamageInterface::StaticClass())))
	{
		IBPI_DamageInterface* InterfaceCallActor = Cast<IBPI_DamageInterface>(GetOwner());
		InterfaceCallActor->Execute_DmgInterfaceApplyEffectCosmeticFrost(GetOwner());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red,
	"DamageComponent::CallDeathOfOwnerInterface -- GetOwner() is not valid Or DOES NOT IMPLEMENT DAMAGE INTERFACE");
	}
}


void UDamageComponent::EndDmgInterfaceApplyEffectCosmeticFrost()
{
	if (IsValid(GetOwner() && GetOwner->GetClass()->ImplementsInterface(UBPI_DamageInterface::StaticClass())))
	{
		IBPI_DamageInterface* InterfaceCallActor = Cast<IBPI_DamageInterface>(GetOwner());
		InterfaceCallActor->Execute_DmgInterfaceApplyEffectCosmeticFrost_End(GetOwner());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red,
	"DamageComponent::CallDeathOfOwnerInterface -- GetOwner() is not valid Or DOES NOT IMPLEMENT DAMAGE INTERFACE");
	}
}