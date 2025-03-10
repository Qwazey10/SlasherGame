// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/EquipmentComponent.h"

#include "Character/SlasherCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Modes/SlasherGameInstance.h"
#include "Structs/ItemStruct.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	SetupEquipmentAttributes();
}


// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UEquipmentComponent::EquipItem_SpawnEquipMesh(int Index, int PrimaryItemIDToEquip)
{
	FName RowName = FName(FString::FromInt(PrimaryItemIDToEquip));
	UWorld* World = GetWorld();
	AActor* Owner = GetOwner();
	ASlasherCharacter* SlasherCharacter = Cast<ASlasherCharacter>(Owner);
	
	
	if (ItemDataTable == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("EquipmentComponent.cpp -- EquipItem_Primary() - ItemDataTable is Null"))
		if (GEngine != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, TEXT("ItemDataTable is Null"));
		}
		
	}
	if (ItemDataTable->GetRowNames().Contains(RowName))
	{
		FItemStruct* ItemStruct = ItemDataTable->FindRow<FItemStruct>(RowName,TEXT("PrimaryItemIDtoEquip"));
		if (ItemStruct->EquipSlot == EEquipmentSlot::Primary)
		{
			//Clear Primary Weapon Reference if it is valid. 
			if (PrimaryWeaponActorReference != nullptr && Index == 0)
			{
				PrimaryWeaponActorReference->Destroy();
				PrimaryWeaponActorReference = nullptr;
			}

			if (SecondaryWeaponActorReference != nullptr && Index == 1)
			{
				SecondaryWeaponActorReference->Destroy();
				SecondaryWeaponActorReference = nullptr;
			}
			
			//Spawn Params for WeaponActor
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			ActorSpawnParams.Owner = GetOwner();
			ActorSpawnParams.bDeferConstruction = true;

			//Spawn Weapon Actor Class
			AWeaponActor* SpawnedWeaponActor = World->SpawnActor<AWeaponActor>(WeaponClass, SlasherCharacter->GetActorLocation(),SlasherCharacter->GetActorRotation(), ActorSpawnParams);
			
			if (SpawnedWeaponActor)
			{
				if (Owner != nullptr && Owner->ActorHasTag("Player"))
				{
					SpawnedWeaponActor->WeaponID = PrimaryItemIDToEquip;
					UGameplayStatics::FinishSpawningActor(SpawnedWeaponActor, SlasherCharacter->GetMesh()->GetSocketTransform(TEXT("Primary")));
					
					if (Index == 0)
					{
						PrimaryWeaponActorReference = SpawnedWeaponActor;
						SpawnedWeaponActor->AttachToComponent(SlasherCharacter->GetMesh(), FAttachmentTransformRules::KeepWorldTransform, TEXT("Primary"));
					}
					if (Index == 1)
					{
						SecondaryWeaponActorReference = SpawnedWeaponActor;
						SpawnedWeaponActor->AttachToComponent(SlasherCharacter->GetMesh(), FAttachmentTransformRules::KeepWorldTransform, TEXT("Secondary"));
					}
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red,TEXT("EquipmentComponent.cpp -- EquipItem_Primary"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("SlasherCharacter.cpp() - Equip Item ID Does not Have a Viable RowName"))
	}
}


void UEquipmentComponent::SetupEquipmentAttributes()
{
	AActor* Owner = GetOwner();
	if (Owner != nullptr && Owner->ActorHasTag("Player"))
	{
		ASlasherCharacter* SlasherCharacter = Cast<ASlasherCharacter>(Owner);

		//Zero Out Bonuses From Equipment for 1-frame //Possible Error but will optimize later if needed. 
		SlasherCharacter->FromEquipment_Health = 0;
		SlasherCharacter->FromEquipment_Mana = 0;
		//Guard Not Implemented

		SlasherCharacter->FromEquipment_Damage = 0;
		SlasherCharacter->FromEquipment_MagicDamageMod = 0;
		SlasherCharacter->FromEquipment_AttackSpeed = 0;

		SlasherCharacter->FromEquipment_Strength = 0;
		SlasherCharacter->FromEquipment_Stamina = 0;
		SlasherCharacter->FromEquipment_Dexterity = 0;
		SlasherCharacter->FromEquipment_Intelligence = 0;

		SlasherCharacter->FromEquipment_Resist_Fire = 0;
		SlasherCharacter->FromEquipment_Resist_Cold = 0;
		SlasherCharacter->FromEquipment_Resist_Detrimental = 0;
		SlasherCharacter->FromEquipment_Resist_Divine = 0;

		//Set Attributes

		SlasherCharacter->Total_Strength = SlasherCharacter->Base_Strength;
		SlasherCharacter->Total_Stamina = SlasherCharacter->Base_Stamina;
		SlasherCharacter->Total_Dexterity = SlasherCharacter->Base_Dexterity;
		SlasherCharacter->Total_Intelligence = SlasherCharacter->Base_Intelligence;

		SlasherCharacter->Total_Resist_Fire = SlasherCharacter->Base_Resist_Fire;
		SlasherCharacter->Total_Resist_Cold = SlasherCharacter->Base_Resist_Cold;
		SlasherCharacter->Total_Resist_Detrimental = SlasherCharacter->Base_Resist_Detrimental;
		SlasherCharacter->Total_Resist_Divine = SlasherCharacter->Base_Resist_Divine;

		UWorld* World = GetWorld();
	
		if (World != nullptr)
		{
			USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(World->GetGameInstance());
			for (int i = 0; i < SlasherGI->Equipment.Num(); i++)
			{
				FString IndexNum = FString::FromInt(i);
				FName RowName = FName(*IndexNum);
				
				if (ItemDataTable->GetRowNames().Contains(RowName))
				{
					
				//Loop Over Equipment and add stats to FromEquipment vars. 
				FItemStruct* ItemStruct = ItemDataTable->FindRow<FItemStruct>(RowName, TEXT("Item"), true);
				SlasherCharacter->FromEquipment_Health += ItemStruct->Health;
				SlasherCharacter->FromEquipment_Mana += ItemStruct->Mana;
				//Todo - Add Guard?
				SlasherCharacter->FromEquipment_Damage += ItemStruct->Damage;
				SlasherCharacter->FromEquipment_AttackSpeed += ItemStruct->AttackSpeed;
				SlasherCharacter->FromEquipment_MagicDamageMod += ItemStruct->MagicDmgMod;

				SlasherCharacter->FromEquipment_Strength += ItemStruct->Strength;
				SlasherCharacter->FromEquipment_Stamina += ItemStruct->Stamina;
				SlasherCharacter->FromEquipment_Dexterity += ItemStruct->Dexterity;
				SlasherCharacter->FromEquipment_Intelligence += ItemStruct->Intelligence;

				SlasherCharacter->FromEquipment_Resist_Fire += ItemStruct->Resist_Fire;
				SlasherCharacter->FromEquipment_Resist_Cold += ItemStruct->Resist_Cold;
				SlasherCharacter->FromEquipment_Resist_Detrimental += ItemStruct->Resist_Detrimental;
				SlasherCharacter->FromEquipment_Resist_Divine += ItemStruct->Resist_Divine;

				SwitchOnEquipPassive(ItemStruct->OnEquipPassive);

				if (i == 6)
					{	
						EquipItem_SpawnEquipMesh(0, SlasherGI->Equipment[i]);
					}
				if (i == 7 && SlasherGI->Equipment[i] > 0)
					{
						EquipItem_SpawnEquipMesh(1, SlasherGI->Equipment[i]);
					}
				}
			}
		//End Loop
		SlasherCharacter->Total_Strength = SlasherCharacter->Base_Strength + SlasherCharacter->FromEquipment_Strength;
		SlasherCharacter->Total_Stamina = SlasherCharacter->Base_Stamina + SlasherCharacter->FromEquipment_Stamina;
		SlasherCharacter->Total_Dexterity = SlasherCharacter->Base_Dexterity + SlasherCharacter->FromEquipment_Dexterity;
		SlasherCharacter->Total_Intelligence = SlasherCharacter->Base_Intelligence + SlasherCharacter->FromEquipment_Intelligence;

		SlasherCharacter->Total_Resist_Fire = SlasherCharacter->Base_Resist_Fire + SlasherCharacter->FromEquipment_Resist_Fire;
		SlasherCharacter->Total_Resist_Cold = SlasherCharacter->Base_Resist_Cold + SlasherCharacter->FromEquipment_Resist_Cold;
		SlasherCharacter->Total_Resist_Detrimental = SlasherCharacter->Base_Resist_Detrimental + SlasherCharacter->FromEquipment_Resist_Detrimental;
		SlasherCharacter->Total_Resist_Divine = SlasherCharacter->Base_Resist_Divine + SlasherCharacter->FromEquipment_Resist_Divine;
		}
	}
}


void UEquipmentComponent::SwitchOnEquipPassive(EOnEquipPassive PassiveEffect)
{
	AActor* Owner = GetOwner();
	if (Owner != nullptr && Owner->ActorHasTag("Player") == true)
	{
		ASlasherCharacter* SlasherCharacter = Cast<ASlasherCharacter>(Owner);
		if (SlasherCharacter != nullptr)
		{
			//zero out Regeneration Effects. 
			//Set Regeneration Effects
			SlasherCharacter->Total_HP_Regeneration = SlasherCharacter->Base_HP_Regeneration;
			SlasherCharacter->FromEquipment_HP_Regeneration = 0.0f;
			SlasherCharacter->Total_MP_Regeneration = SlasherCharacter->Base_MP_Regeneration;
			SlasherCharacter->FromEquipment_MP_Regeneration = 0.0f;
			SlasherCharacter->Total_Guard_Regeneration = SlasherCharacter->Base_Guard_Regeneration;
			SlasherCharacter->FromEquipment_Guard_Regeneration = 0.0f;


	//Boolean Sets for Passive Gear -- This is for Stop All Casting Passive 
			SlasherCharacter->bCanCast = true;
	//This is a temp solution to correct if we unequip silence mechanic item, which will set onEquip Below.


	switch (PassiveEffect)
	{
	case EOnEquipPassive::Null:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: Null"));
			break;
		}

	case EOnEquipPassive::HPRegeneration_Small:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: HPRegeneration - Small"));
			SlasherCharacter->FromEquipment_HP_Regeneration = +1.0f;
			break;
		}
	case EOnEquipPassive::HPRegeneration_Medium:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: HPRegeneration - Med"));
			SlasherCharacter->FromEquipment_HP_Regeneration = +2.0f;
			break;
		}
	case EOnEquipPassive::HPRegeneration_Large:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: HPRegeneration - Large"));
			SlasherCharacter->FromEquipment_HP_Regeneration = +3.0f;
			break;
		}
	case EOnEquipPassive::ManaRegeneration_Small:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: Mana Regen - Small"));
			SlasherCharacter->FromEquipment_MP_Regeneration = +1.0f;
			break;
		}
	case EOnEquipPassive::ManaRegeneration_Medium:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: Mana Regen - Medium"));
			break;
		}
	case EOnEquipPassive::ManaRegeneration_Large:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: Mana Regen - Large"));
			SlasherCharacter->FromEquipment_MP_Regeneration = +2.0f;
			break;
		}
	case EOnEquipPassive::MovementSpeed_Small:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: MovementSpeed - Small"));
			SlasherCharacter->FromEquipment_MP_Regeneration = +3.0f;
			
			break;
		}
	case EOnEquipPassive::MovementSpeed_Medium:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: MovementSpeed - Medium"));
			break;
		}
	case EOnEquipPassive::MovementSpeed_Large:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: MovementSpeed - Large"));
			break;
		}
	case EOnEquipPassive::DrainHP_Small:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: DrainHP_Small"));
			SlasherCharacter->FromEquipment_HP_Regeneration = -1.0f;
			break;
		}
	case EOnEquipPassive::DrainHP_Medium:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: DrainHP_Medium"));
			SlasherCharacter->FromEquipment_HP_Regeneration = -2.0f;
			break;
		}
	case EOnEquipPassive::DrainHP_Large:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: DrainHP_Large"));
			SlasherCharacter->FromEquipment_HP_Regeneration = -3.0f;
			break;
		}
	case EOnEquipPassive::GuardRegen_Small:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: GuardRegen - Small"));
			break;
		}
	case EOnEquipPassive::GuardRegen_Medium:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: GuardRegen - Medium"));
			break;
		}
	case EOnEquipPassive::GuardRegen_Large:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: GuardRegen - Large"));
			break;
		}
	case EOnEquipPassive::DisableAllCasting:
		{
			SlasherCharacter->bCanCast = false;
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: Disable All Casting"));
			break;
		}
	} //end switch
	}
	}
}