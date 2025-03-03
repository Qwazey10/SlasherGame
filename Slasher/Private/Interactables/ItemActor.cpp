// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/ItemActor.h"
#include "DrawDebugHelpers.h"
#include "Structs/ItemStruct.h"
#include "Modes/SlasherGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"


// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Tags.Add(FName("Item"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	//Set Physics
	Mesh->SetSimulatePhysics(true); //Enable Simulate Physics
	Mesh->SetNotifyRigidBodyCollision(true); // Required to fire the hit event

	//Init Buoyancy Component
	BuoyancyComponent = CreateDefaultSubobject<UBuoyancyComponent>(TEXT("Buoyancy"));
	
	//Define Pontoon 0
	Pontoon_00.CenterSocket = FName("None");
	Pontoon_00.Radius = 20.0f;
	Pontoon_00.RelativeLocation = FVector(0.0f, 0.0f, 0.0f);
	BuoyancyComponent->BuoyancyData.Pontoons.Add(Pontoon_00);
	BuoyancyComponent->BuoyancyData.bApplyDragForcesInWater = true;
	
}

void AItemActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
		// BP Style Construction Script
	Constructor_SetupItem((SpawnItemID));

	
}


// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	BeginPlay_SetupItem(SpawnItemID);
	
	SetMassFromDataTable();

	// Set DataTable Mass For ITem
	//Gets the Item From the DataTable //Maybe change
	//FString BeginPlayDebugMessage = Struct.ItemName;
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, BeginPlayDebugMessage);
	
		//UStaticMesh* LoadMesh = Struct.ItemDisplayMesh;
		//Mesh->SetStaticMesh(LoadMesh);
	

	//Struct = ReturnItemStruct(SpawnItemID);
	//Sets the items from the datatable. 
	//Mesh->SetStaticMesh(LoadMesh);
	//Mesh->SetWorldTransform(Struct.ItemDisplayMeshTransform);
	// Audio Attributes
	

	
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemActor::Constructor_SetupItem(int SetupItemID)
{
	if (ItemDataTable != nullptr)
	{
		FString ItemIDToString = FString::FromInt(SetupItemID);
		FName RowName = FName(*ItemIDToString);

		if (ItemDataTable->GetRowNames().Contains(RowName))
		{
			UE_LOG(LogTemp, Warning, TEXT("Item Data Table Row Found"));
			FItemStruct* LookupItemStruct = ItemDataTable->FindRow<FItemStruct>(RowName, TEXT("Item"), true);

			

			if (LookupItemStruct->ItemDisplayMesh != nullptr)
			{
				Mesh->SetStaticMesh(LookupItemStruct->ItemDisplayMesh);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Item Display Mesh is not valid"));
			}
			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Item Data Table Not Found, Destroying Item"));
			Destroy();
		}
	}
}

void AItemActor::BeginPlay_SetupItem(int SetupItemID)
{
	if (ItemDataTable != nullptr)
	{
		FString ItemIDToString = FString::FromInt(SetupItemID);
		FName RowName = FName(*ItemIDToString);

		if (ItemDataTable->GetRowNames().Contains(RowName))
		{
			
			FItemStruct* LookupItemStruct = ItemDataTable->FindRow<FItemStruct>(RowName, TEXT("Item"), true);

			ItemUseSound = LookupItemStruct->ItemUseSound;
			ItemPickUpSound = LookupItemStruct->ItemPickUpSound;
			ItemDestroySound = LookupItemStruct->ItemDestroySound;
			ItemAttenuation = LookupItemStruct->ItemAttenuation;
	
			//Setup Item Attributes
			ItemID = LookupItemStruct->ItemID;
			ItemName = LookupItemStruct->ItemName;
			ItemDescription = LookupItemStruct->ItemDescription;
			Strength = LookupItemStruct->Strength;
			Stamina = LookupItemStruct->Stamina;
			Dexterity = LookupItemStruct->Dexterity;
			Intelligence = LookupItemStruct->Intelligence;

			//Damage Attributes
			Damage = LookupItemStruct->Damage;
			AttackSpeed = LookupItemStruct->AttackSpeed;
			MagicDmgMod = LookupItemStruct->MagicDmgMod;

			//Defensive Attributes
			Armor = LookupItemStruct->Armor;
			Resist_Fire = LookupItemStruct->Resist_Fire;
			Resist_Cold = LookupItemStruct->Resist_Cold;
			Resist_Detrimental = LookupItemStruct->Resist_Detrimental;
			Resist_Divine = LookupItemStruct->Resist_Divine;
	
			// OnUse Ability Descriptions 
			OnUse_ActivateAbilityID = LookupItemStruct->OnUse_ActivateAbilityID;
			Power =	LookupItemStruct->Power;
			Description_00 = LookupItemStruct->Description_00;
			AbilityMod_00 = LookupItemStruct->AbilityMod_00;
			Description_01 = LookupItemStruct->Description_01;
			AbilityMod_01 = LookupItemStruct->AbilityMod_01;
			Description_02 = LookupItemStruct->Description_02;
			AbilityMod_02 = LookupItemStruct->AbilityMod_02;
			Description_03 = LookupItemStruct->Description_03;
			AbilityMod_03 = LookupItemStruct->AbilityMod_03;

			//Utilities
			SalePrice = LookupItemStruct->SalePrice;
			Weight = LookupItemStruct->Weight;

			//Set Physics Interactions Audio DataAsset
			if (LookupItemStruct->InteractionAudioDataAsset)
			{
				PhysicsInteractionAudioDataAsset = LookupItemStruct->InteractionAudioDataAsset;
			}
			else
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT(" ItemActor.cpp -- BeginPlay_Setup() -- PhysicsInteractionAudioDataAsset is Null")));
				}
			}

			
		}
		else
		{
			
			FString BeginPlayDebugMessage = FString::Printf(TEXT(" ItemActor.cpp -- BeginPlay_Setup() -- Item Data Table Not Found! Invalid ItemID"));
			GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, BeginPlayDebugMessage);
			
		}
	}
}



//BPI_PlayerToInteractable
void AItemActor::PlayerToInteractable_InputInteractPressed_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, "Item Actor Player Interact Press Received");
}

void AItemActor::PlayerToInteractable_HighlightTrace_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, "InteractTrace Interface Event From ItemActor");
}

void AItemActor::PlayerToInteractable_CustomDepthFilterOn_Implementation()
{
	Mesh->SetRenderCustomDepth(true);
	Mesh->SetCustomDepthStencilValue(1);
	//IBPI_PlayerToInteractable::PlayerToInteractable_CustomDepthFilterOn_Implementation();
}

void AItemActor::PlayerToInteractable_CustomDepthFilterOff_Implementation()
{
	Mesh->SetRenderCustomDepth(false);
	Mesh->SetCustomDepthStencilValue(0);
	//IBPI_PlayerToInteractable::PlayerToInteractable_CustomDepthFilterOff_Implementation();
}

/**
 * This function is called whenever this actor registers a collision with another object.
 * It processes the collision to trigger associated audio effects and debug visualization
 * based on the impact force and material properties of the hit surface.
 *
 * @param MyComp The component of this actor that initiated the collision.
 * @param Other The other actor this actor collided with. //TODO - Create a Filter here if design needs, glass on wood, metal on wood etc. 
 * @param OtherComp The component of the other actor involved in the collision.
 * @param bSelfMoved Whether this actor initiated the movement that caused the hit.
 * @param HitLocation The world location where the collision occurred.
 * @param HitNormal The world normal vector at the collision point.
 * @param NormalImpulse The impulse applied to this actor as a result of the collision.
 * @param Hit Detailed information about the hit, including physical surface type and collision impact data.
 */

void AItemActor::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
                           FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	
	float NormalImpulseLength = NormalImpulse.Size();
	PhysicsImpactLocation = HitLocation;

	if (PhysicsInteractionAudioDataAsset)
	{
		if (NormalImpulseLength > 1000.0f)
		{
			if (bCanAudioPhysicsTriggerHit)
			{
				EPhysicalSurface PhysSurf = Hit.PhysMaterial->SurfaceType;
				FRotator Rotation = GetActorRotation();
				
				float NormalizedForce = UKismetMathLibrary::NormalizeToRange (NormalImpulseLength, 0.0f, 50000.0f);
				if (NormalizedForce >= 0.1f && NormalizedForce <= 1.0f)
				{
					BPAudio_ItemActorPhysicsImpact_Light();
					if (bShowPhysicsImpactAudioDebugSpheres)
					{
						ItemActor_DrawDebugSphere(HitLocation, 25.0f, FColor::Green, 10.0f, false);
					}
					UGameplayStatics::PlaySoundAtLocation(this, SwitchAudioOnPhysMaterial(PhysSurf, 1), GetActorLocation(), Rotation, NormalizedForce, 1, 0,PhysicsInteractionAudioDataAsset->PhysicsImpact_SoundAttenuation_Heavy);
					GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("Normalized Force: %f"), NormalizedForce));
				}
				
				else if (NormalizedForce > 1.0f && NormalizedForce <= 2.0f)
				{
				
					if (bShowPhysicsImpactAudioDebugSpheres)
					{
						ItemActor_DrawDebugSphere(HitLocation, 25.0f, FColor::Orange, 10.0f, false);
					}
					BPAudio_ItemActorPhysicsImpact_Medium();
					UGameplayStatics::PlaySoundAtLocation(this, SwitchAudioOnPhysMaterial(PhysSurf, 2), GetActorLocation(), Rotation, NormalizedForce, 1, 0,PhysicsInteractionAudioDataAsset->PhysicsImpact_SoundAttenuation_Heavy);
					GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Orange, FString::Printf(TEXT("Normalized Force: %f"), NormalizedForce));
				
				}
				
				else if (NormalizedForce > 2.0f)
				{
					if (bShowPhysicsImpactAudioDebugSpheres)
					{
						ItemActor_DrawDebugSphere(HitLocation, 25.0f, FColor::Orange, 10.0f, false);
					}
					UGameplayStatics::PlaySoundAtLocation(this, SwitchAudioOnPhysMaterial(PhysSurf, 3), GetActorLocation(), Rotation, NormalizedForce, 1, 0,PhysicsInteractionAudioDataAsset->PhysicsImpact_SoundAttenuation_Heavy);
					BPAudio_ItemActorPhysicsImpact_Heavy();
					GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Normalized Force: %f"), NormalizedForce));
				}
				
				StartPhysicsHitTimer();
				bCanAudioPhysicsTriggerHit = false;
			}

		}
	}
	
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, FString::Printf(TEXT("ItemActor.cpp -- PhysicsImpactAudioDataAsset is Null")));
	}
}

//This is the timer manager called from physics interaction hit event, this timer will block multiple hit events from triggering
void AItemActor::StartPhysicsHitTimer()
{
	
	GetWorld()->GetTimerManager().SetTimer(
	 HitTimerHandle,
	 this,
	 &AItemActor::ResetHitTimer,
	 0.5f,
	 false);
	
}

void AItemActor::ResetHitTimer()
{
	bCanAudioPhysicsTriggerHit = true;
}


void AItemActor::AddSelfToInventory()
{
	
	USlasherGameInstance* GameInstance = Cast<USlasherGameInstance>(GetWorld()->GetGameInstance());
	GameInstance->Inventory.Add(ItemID);
	BPAudio_ItemPickupAudio();
	Destroy();
	
}

void AItemActor::BPAudio_ItemPickupAudio_Implementation()
{
	//Audio BP Function for when an item is picked up.
	UGameplayStatics::PlaySoundAtLocation(this, ItemPickUpSound, GetActorLocation());
}

void AItemActor::BPAudio_ItemActorPhysicsImpact_Light_Implementation()
{
	//Audio BP Call for when an Item Impacts objects. 
}
void AItemActor::BPAudio_ItemActorPhysicsImpact_Medium_Implementation()
{
	//Audio BP Call for when an Item Impacts objects. 
}
void AItemActor::BPAudio_ItemActorPhysicsImpact_Heavy_Implementation()
{
	//Audio BP Call for when an Item Impacts objects. 
}

void AItemActor::ItemActor_DrawDebugSphere(FVector Location, float Radius, FColor Color, float Duration,
	bool bPersistentLines)
{

	const UWorld *World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("Draw Debug Sphere -- Draw.cpp -- World Is Null"));
		return;
	}

	// DrawDebugSphere parameters:
	// - World: The world context.
	// - Location: Center of the sphere.
	// - Radius: Radius of the sphere.
	// - Segments: Number of segments for smoothness (higher = smoother).
	// - Color: Color of the sphere.
	// - bPersistentLines: Whether the sphere persists indefinitely.
	// - Lifetime: How long the sphere lasts in seconds (ignored if bPersistentLines is true).
	// - Thickness: Line thickness of the sphere.

	DrawDebugSphere(
		World,            // World context
		Location,         // Sphere location
		Radius,           // Sphere radius
		12,               // Number of segments
		Color,            // Sphere color
		bPersistentLines, // Persistent lines
		Duration,         // Duration in seconds
		0,                // Depth priority (0 = foreground)
		1.0f              // Line thickness
	);
	
}

 //Impact Classification int is the representation of 1-3 to Light, Medium, Heavy - From NotifyHit Function. 
USoundCue* AItemActor::SwitchAudioOnPhysMaterial(EPhysicalSurface PhysicalMaterial, int ImpactClassificationInt)
{
	switch (PhysicalMaterial)
	{
	default:
		{
			return PhysicsInteractionAudioDataAsset->PhysicsImpact_Default_Light_00;
		
		}
		
		
	case SurfaceType_Default:
		{
			if (ImpactClassificationInt == 1)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Default_Light_00;
			}
				
			if (ImpactClassificationInt == 2)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Default_Medium_00;
			}
			
			if (ImpactClassificationInt == 3)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Default_Heavy_00;
			}
			
		}
		
	case SurfaceType1: // Wood
		{
			if (ImpactClassificationInt == 1)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Wood_Light_00;
			}
				
			if (ImpactClassificationInt == 2)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Wood_Medium_00;
			}
			
			if (ImpactClassificationInt == 3)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Wood_Heavy_00;
			}
		}
	case SurfaceType2: // Stone
		{
			if (ImpactClassificationInt == 1)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Stone_Light_00;
			}
				
			if (ImpactClassificationInt == 2)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Stone_Medium_00;
			}
			
			if (ImpactClassificationInt == 3)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Stone_Heavy_00;
			}
		}


	case SurfaceType3: // Metal
		{
			if (ImpactClassificationInt == 1)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Metal_Light_00;
			}
				
			if (ImpactClassificationInt == 2)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Metal_Medium_00;
			}
			if (ImpactClassificationInt == 3)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Metal_Heavy_00;
			}			
		}

	case SurfaceType4: // Water
		{
			if (ImpactClassificationInt == 1)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Water_Light_00;
			}
				
			if (ImpactClassificationInt == 2)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Water_Medium_00;
			}
			
			if (ImpactClassificationInt == 3)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Water_Heavy_00;
			}			
		}
	
	case SurfaceType5: // Glass
		{
			if (ImpactClassificationInt == 1)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Glass_Light_00;
			}
				
			if (ImpactClassificationInt == 2)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Glass_Medium_00;
			}
			
			if (ImpactClassificationInt == 3)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Glass_Heavy_00;
			}
			
		}
		
	case SurfaceType6: // Grass
		{
			if (ImpactClassificationInt == 1)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Grass_Light_00;
			}
				
			if (ImpactClassificationInt == 2)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Grass_Medium_00;
			}
			
			if (ImpactClassificationInt == 3)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Grass_Heavy_00;
			}
			
		}
	
	case SurfaceType7: // Slime
		{
			if (ImpactClassificationInt == 1)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Slime_Light_00;
			}
				
			if (ImpactClassificationInt == 2)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Slime_Medium_00;
			}
			
			if (ImpactClassificationInt == 3)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Slime_Heavy_00;
			}
			
		}
	case SurfaceType8: //Lava
		{
			if (ImpactClassificationInt == 1)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Lava_Light_00;
			}
				
			if (ImpactClassificationInt == 2)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Lava_Medium_00;
			}
			
			if (ImpactClassificationInt == 3)
			{
				return PhysicsInteractionAudioDataAsset->PhysicsImpact_Lava_Heavy_00;
			}
			
		}
	}
	return PhysicsInteractionAudioDataAsset->PhysicsImpact_Default_Light_00;
}

/*
 *		Surface Type Definitions from Project Settings. 
 *		
 *		Surface Type 1 - Wood
 *		SurFace Type 2 - Stone
 *		Surface Type 3 - Metal
 *		Surface Type 4 - Water
 *		Surface Type 5 - Glass
 *		Surface type 6 - Grass
 *		Surface type 7 - Slime
 *		Surface type 8 - Lava/Magma
 *		
 */


void AItemActor::SetMassFromDataTable()
{
	
	if (ItemDataTable != nullptr)
	{
		FString ItemIDToString = FString::FromInt(SpawnItemID);
		FName RowName = FName(*ItemIDToString);

		if (ItemDataTable->GetRowNames().Contains(RowName))
		{
			UE_LOG(LogTemp, Warning, TEXT("Item Data Table Row Found"));
			FItemStruct* LookupItemStruct = ItemDataTable->FindRow<FItemStruct>(RowName, TEXT("Item"), true);
			Mesh->SetMassOverrideInKg("None",LookupItemStruct->ItemPhysicsMass);
		}
	}	
}