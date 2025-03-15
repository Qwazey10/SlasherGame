/*
 *
 *This Actor is the primary Debug actor for Slasher Character, it includes the header files for ImGui, To use this,
 *You need to include it on the actor you wish to use. UPROPERTY and then create the default subobject. 
 *
 */

// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorComponent/AC_ImGuiActorDebug.h"
#include "Interfaces/BPI_PlayerToEnemy.h"
#include "DrawDebugHelpers.h"
#include "Enemy/EnemyBase.h"
#include "imgui.h"
#include "Animation/SlasherChrAnimInstance.h"
#include "Interactables/ItemActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/SlasherCharacter.h"
#include "Modes/SlasherGameInstance.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UAC_ImGuiActorDebug::UAC_ImGuiActorDebug()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_ImGuiActorDebug::BeginPlay()
{
	Super::BeginPlay();
	OwnerReference = GetOwner();


	// ...
}


// Called every frame
void UAC_ImGuiActorDebug::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//void UImGuiActorDebug::DisplayInventoryWindow()
//{
//		AActor* Owner = GetOwner();
//		UWorld* World = GetOwner()->GetWorld();
//		USlasherGameInstance* GameInstance = Cast<USlasherGameInstance>(UGameplayStatics::GetGameInstance(GetOwner()->GetWorld()));;
//		if (GameInstance)
//		{
//			ImGui::Begin("PlayerInventory");
//			// Assuming Inventory is a TArray<int> or similar
//			for (int i = 0; i < GameInstance->Inventory.Num(); ++i)
//			{
//				// Set a color for each item (example: alternating colors)
//				ImVec4 color = (i % 2 == 0) ? ImVec4(1.0f, 0.5f, 0.0f, 1.0f) // Orange for even indices
//											: ImVec4(0.0f, 0.5f, 1.0f, 1.0f); // Blue for odd indices
//        
//				// Display the value with the chosen color
//				ImGui::TextColored(color, "Item %d: %d", i, GameInstance->Inventory[i]);
//				
//			}                        
//			ImGui::End();
//}
//	}


void UAC_ImGuiActorDebug::DisplayDebug_PlayerCharacter(AActor* Owner)
{
	//Declarations
	static constexpr ImVec4 ImGui_COLOR_RED = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Full red
	static constexpr ImVec4 ImGui_COLOR_GREEN = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // Full green
	static constexpr ImVec4 ImGui_COLOR_BLUE = ImVec4(0.0f, 0.0f, 1.0f, 1.0f); // Full blue
	static constexpr ImVec4 ImGui_COLOR_YELLOW = ImVec4(1.0f, 1.0f, 0.0f, 1.0f); // Yellow (red + green)
	static constexpr ImVec4 ImGui_COLOR_CYAN = ImVec4(0.0f, 1.0f, 1.0f, 1.0f); // Cyan (green + blue)
	static constexpr ImVec4 ImGui_COLOR_MAGENTA = ImVec4(1.0f, 0.0f, 1.0f, 1.0f); // Magenta (red + blue)
	static constexpr ImVec4 ImGui_COLOR_WHITE = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // White
	static constexpr ImVec4 ImGui_COLOR_BLACK = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // Black
	static constexpr ImVec4 ImGui_COLOR_GRAY = ImVec4(0.5f, 0.5f, 0.5f, 1.0f); // Gray
	static constexpr ImVec4 ImGui_COLOR_LIGHT_GRAY = ImVec4(0.8f, 0.8f, 0.8f, 1.0f); // Light gray
	static constexpr ImVec4 ImGui_COLOR_DARK_GRAY = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); //Dark Grey

	if (Owner->ActorHasTag("Player"))
	{
		ASlasherCharacter* Character = Cast<ASlasherCharacter>(Owner);

		UWorld* World = Character->GetWorld();
		USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(World->GetGameInstance());


		ImGui::Begin("MainPlayerCharacterDebug");

		ImGui::SeparatorText("Player Status");
		ImGui::TextColored(ImGui_COLOR_WHITE, "LEVEL: %d", Character->Level);
		ImGui::TextColored(ImGui_COLOR_WHITE, "EXPERIENCE: %.0f/%.0f", SlasherGI->GI_CurrentExperience,Character->ExperienceToNextLevel);
		ImGui::SeparatorText("Player Status");
		ImGui::TextColored(ImGui_COLOR_GREEN, "HEALTH: %.0f/%.0f", Character->CurrentHealth, Character->MaxHealth);
		ImGui::TextColored(ImGui_COLOR_CYAN, "MANA: %.0f/%.0f", Character->CurrentMana, Character->MaxMana);
		ImGui::TextColored(ImGui_COLOR_WHITE, "(NOT IMPLEMENTED) GUARD: %.0f", Character->Base_Guard);
		//Todo -- guard is not implemented
		ImGui::SeparatorText("Attributes");
		ImGui::TextColored(ImGui_COLOR_YELLOW, "STRENGTH: %.0f", Character->Total_Strength);
		ImGui::TextColored(ImGui_COLOR_GREEN, "STAMINA: %.0f", Character->Total_Stamina);
		ImGui::TextColored(ImGui_COLOR_MAGENTA, "DEXTERITY: %.0f", Character->Total_Dexterity);
		ImGui::TextColored(ImGui_COLOR_CYAN, "INTELLIGENCE: %.0f", Character->Total_Intelligence);
		ImGui::SeparatorText("Damage");
		ImGui::TextColored(ImGui_COLOR_WHITE, "DAMAGE: %.0f", Character->Total_Damage);
		ImGui::TextColored(ImGui_COLOR_GREEN, "ATTACK SPEED: %.0f", Character->Total_AttackSpeed);
		ImGui::TextColored(ImGui_COLOR_CYAN, "MAGIC DMG MOD: %.0f", Character->Total_MagicDamageMod);
		ImGui::SeparatorText("Defensive");
		ImGui::TextColored(ImGui_COLOR_WHITE, "ARMOR: %.0f/", Character->Total_Armor);
		ImGui::TextColored(ImGui_COLOR_RED, "RESIST FIRE: %.0f", Character->Total_Resist_Fire);
		ImGui::TextColored(ImGui_COLOR_CYAN, "RESIST COLD: %.0f", Character->Total_Resist_Cold);
		ImGui::TextColored(ImGui_COLOR_GREEN, "RESIST DETRIMENTAL: %.0f", Character->Total_Resist_Detrimental);
		ImGui::TextColored(ImGui_COLOR_WHITE, "MAGIC DIVINE: %.0f", Character->Total_Resist_Divine);


		if (ImGui::CollapsingHeader("Show Inventory"))
		{
			AActor* InventoryOwner = GetOwner();
			if (InventoryOwner->ActorHasTag("Player"))
			{
				DebugDisplayInventory();
			}
		}

		static bool ToggleUtilityWindow = false;
		if (ImGui::Button("Toggle Utility"))
		{
			ToggleUtilityWindow = !ToggleUtilityWindow;
		}
		if (ToggleUtilityWindow)
		{
			UtilityFunctionWindow();
		}

		
		if (ImGui::CollapsingHeader("Save/Load Debug Menu"))
		{
			AActor* OwnerActor = GetOwner();
			if (OwnerActor->ActorHasTag("Player"))
			{
				SaveLoadTestFunctions();
			}
		}
		ImGui::End();
	}
}


void UAC_ImGuiActorDebug::TravelToLevel(FString LevelName)
{
	UWorld* World = GetOwner()->GetWorld();
	UGameplayStatics::OpenLevel(World, FName(*LevelName));
}


void UAC_ImGuiActorDebug::DisplayDebug_Enemy(FHitResult* HitResult)
{
	if (HitResult->Actor->ActorHasTag("Enemy"))
	{
		AEnemyBase* EnemyActor = Cast<AEnemyBase>(HitResult->Actor);
		FString OwnerName = "HelloFriends";
		ImGui::Begin("Enemy Display Debug Interact Trace");
		ImGui::Text("EnemyName -- %s ", TCHAR_TO_UTF8(*OwnerName));
		ImGui::Text("Current Health: %f", 420.0f);
		ImGui::Text("Current Mana: %f", 69.0f);
		ImGui::Text("Current Armor: %f", 123.0f);
		ImGui::End();
	}
}

void UAC_ImGuiActorDebug::DisplayDebug_Item(FHitResult* HitResult)
{
	static constexpr ImVec4 ImGui_COLOR_RED = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Full red
	static constexpr ImVec4 ImGui_COLOR_GREEN = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // Full green
	static constexpr ImVec4 ImGui_COLOR_BLUE = ImVec4(0.0f, 0.0f, 1.0f, 1.0f); // Full blue
	static constexpr ImVec4 ImGui_COLOR_YELLOW = ImVec4(1.0f, 1.0f, 0.0f, 1.0f); // Yellow (red + green)
	static constexpr ImVec4 ImGui_COLOR_CYAN = ImVec4(0.0f, 1.0f, 1.0f, 1.0f); // Cyan (green + blue)
	static constexpr ImVec4 ImGui_COLOR_MAGENTA = ImVec4(1.0f, 0.0f, 1.0f, 1.0f); // Magenta (red + blue)
	static constexpr ImVec4 ImGui_COLOR_WHITE = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // White
	static constexpr ImVec4 ImGui_COLOR_BLACK = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // Black
	static constexpr ImVec4 ImGui_COLOR_GRAY = ImVec4(0.5f, 0.5f, 0.5f, 1.0f); // Gray
	static constexpr ImVec4 ImGui_COLOR_LIGHT_GRAY = ImVec4(0.8f, 0.8f, 0.8f, 1.0f); // Light gray
	static constexpr ImVec4 ImGui_COLOR_DARK_GRAY = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); //Dark Grey


	if (HitResult->Actor->ActorHasTag("Item"))
	{
		AItemActor* ItemActor = Cast<AItemActor>(HitResult->Actor);


		ImGui::Begin("Debug Item Display");

		//ImGui::ColorEdit4("Color", reinterpret_cast<float*>(&AttributeColor)); // Test ColorPicker For Now

		//Item Description
		ImGui::SeparatorText("Item Description");
		ImGui::Text("Item ID: %d", ItemActor->ItemID);
		ImGui::TextColored(ImGui_COLOR_WHITE, "Item Name -- %s ", TCHAR_TO_UTF8(*ItemActor->ItemName));
		ImGui::TextColored(ImGui_COLOR_WHITE, "Item Description -- %s ", TCHAR_TO_UTF8(*ItemActor->ItemDescription));

		//Damage  Modifiers
		ImGui::SeparatorText("Item Damage Mods");
		ImGui::TextColored(ImGui_COLOR_WHITE, "DAMAGE: %f", ItemActor->Damage);
		ImGui::TextColored(ImGui_COLOR_WHITE, "ATTACK SPEED: %f", ItemActor->AttackSpeed);
		ImGui::TextColored(ImGui_COLOR_WHITE, "MAGIC DMG MOD: %f", ItemActor->MagicDmgMod);

		//Item Attributes
		ImGui::SeparatorText("Item Attributes");
		ImGui::TextColored(ImGui_COLOR_GREEN, "HEALTH: %f", ItemActor->Health);
		ImGui::TextColored(ImGui_COLOR_CYAN, "MANA: %f", ItemActor->Mana);
		ImGui::TextColored(ImGui_COLOR_YELLOW, "STRENGH: %f", ItemActor->Strength);
		ImGui::TextColored(ImGui_COLOR_GREEN, "STAMINA: %f", ItemActor->Stamina);
		ImGui::TextColored(ImGui_COLOR_CYAN, "DEXTERITY: %f", ItemActor->Dexterity);
		ImGui::TextColored(ImGui_COLOR_BLUE, "INTELLIGENCE: %f", ItemActor->Intelligence);

		//Defensive Stats Separator
		ImGui::SeparatorText("Defensive Stats");
		ImGui::TextColored(ImGui_COLOR_GRAY, "ARMOR: %f", ItemActor->Armor);
		ImGui::TextColored(ImGui_COLOR_RED, "RESIST FIRE: %f", ItemActor->Resist_Fire);
		ImGui::TextColored(ImGui_COLOR_CYAN, "RESIST COLD: %f", ItemActor->Resist_Cold);
		ImGui::TextColored(ImGui_COLOR_GREEN, "RESIST DETRIMENTAL: %f", ItemActor->Resist_Detrimental);
		ImGui::TextColored(ImGui_COLOR_WHITE, "RESIST DIVINE: %f", ItemActor->Resist_Divine);

		//Utility
		ImGui::SeparatorText("Utility");
		ImGui::TextColored(ImGui_COLOR_GRAY, "SALE PRICE: %f", ItemActor->SalePrice);
		ImGui::TextColored(ImGui_COLOR_GRAY, "WEIGHT: %f", ItemActor->Weight);

		//OnUse Data
		ImGui::SeparatorText("OnUse Data");
		ImGui::TextColored(ImGui_COLOR_LIGHT_GRAY, "ON USE: %d", ItemActor->OnUse_ActivateAbilityID);
		ImGui::TextColored(ImGui_COLOR_LIGHT_GRAY, "ON USE POWER: %f", ItemActor->Power);
		ImGui::TextColored(ImGui_COLOR_DARK_GRAY, "AbilityMod Description: %s",
		                   TCHAR_TO_UTF8(*ItemActor->Description_00));
		ImGui::TextColored(ImGui_COLOR_GREEN, "ABILITY MOD 1 POWER: %f", ItemActor->AbilityMod_00);
		ImGui::TextColored(ImGui_COLOR_LIGHT_GRAY, "ON USE: %s", TCHAR_TO_UTF8(*ItemActor->Description_01));
		ImGui::TextColored(ImGui_COLOR_GREEN, "ABILITY MOD 2 POWER: %f", ItemActor->AbilityMod_01);
		ImGui::TextColored(ImGui_COLOR_LIGHT_GRAY, "ON USE: %s", TCHAR_TO_UTF8(*ItemActor->Description_02));
		ImGui::TextColored(ImGui_COLOR_GREEN, "ABILITY MOD 3 POWER: %f", ItemActor->AbilityMod_02);
		ImGui::TextColored(ImGui_COLOR_LIGHT_GRAY, "ON USE: %s", TCHAR_TO_UTF8(*ItemActor->Description_03));
		ImGui::TextColored(ImGui_COLOR_GREEN, "ABILITY MOD 4 POWER: %f", ItemActor->AbilityMod_03);


		ImGui::End();
	}
}

void UAC_ImGuiActorDebug::BeginPlay_GetOwnerReference()
{
}

void UAC_ImGuiActorDebug::EnemyDebugInteractTrace()
{
	//Init Traces
	FHitResult Hit;
	TArray<AActor*> ActorsToIgnore;
	float TraceDistance = 10000.0f;
	FVector StartLocation = GetOwner()->GetActorLocation();
	FVector EndLocation = GetOwner()->GetActorForwardVector() * TraceDistance;
	//Start Line Trace
	const bool bHit = UKismetSystemLibrary::LineTraceSingle(
		this,
		StartLocation,
		EndLocation,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration, Hit,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		1.0f
	);

	//Hit Logic
	if (bHit && Hit.Actor->ActorHasTag(FName("Enemy")))
	{
		FString HitEnemyName = Hit.Actor->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, HitEnemyName);
		AEnemyBase* EnemyReference = Cast<AEnemyBase>(Hit.Actor);
	}

	if (bHit && Hit.Actor->ActorHasTag(FName("Item")))
	{
		FString HitItemName = Hit.Actor->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, HitItemName);
	}

	if (bHit && Hit.Actor->Implements<UBPI_PlayerToEnemy>())
	{
		FString ImpInterface = "HelloFriend - I implement BPI_PlayerToEnemy";
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, ImpInterface);
	}
}


void UAC_ImGuiActorDebug::UtilityFunctionWindow()
{
	static constexpr ImVec4 ImGui_COLOR_RED = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Full red
	static constexpr ImVec4 ImGui_COLOR_GREEN = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // Full green
	static constexpr ImVec4 ImGui_COLOR_BLUE = ImVec4(0.0f, 0.0f, 1.0f, 1.0f); // Full blue
	static constexpr ImVec4 ImGui_COLOR_YELLOW = ImVec4(1.0f, 1.0f, 0.0f, 1.0f); // Yellow (red + green)
	static constexpr ImVec4 ImGui_COLOR_CYAN = ImVec4(0.0f, 1.0f, 1.0f, 1.0f); // Cyan (green + blue)
	static constexpr ImVec4 ImGui_COLOR_MAGENTA = ImVec4(1.0f, 0.0f, 1.0f, 1.0f); // Magenta (red + blue)
	static constexpr ImVec4 ImGui_COLOR_WHITE = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // White
	static constexpr ImVec4 ImGui_COLOR_BLACK = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // Black
	static constexpr ImVec4 ImGui_COLOR_GRAY = ImVec4(0.5f, 0.5f, 0.5f, 1.0f); // Gray
	static constexpr ImVec4 ImGui_COLOR_LIGHT_GRAY = ImVec4(0.8f, 0.8f, 0.8f, 1.0f); // Light gray
	static constexpr ImVec4 ImGui_COLOR_DARK_GRAY = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); //Dark Grey


	ImGui::Begin("Utility Functions");
	if (ImGui::CollapsingHeader("SpawnItem"))
	{
		static int ItemIDToSpawn;
		ImGui::TextColored(ImGui_COLOR_WHITE, "SpawnItem");
		ImGui::InputInt("Item ID", &ItemIDToSpawn);
		if (ImGui::Button("Spawn Item"))
		{
			SpawnItem(ItemIDToSpawn);
		}
	}
	if (ImGui::CollapsingHeader("Debug Trace Toggle"))
	{
		//Toggle LineTrace To Debug Item. 
		if (ImGui::Button("Toggle Debug Item Trace"))
		{
			AActor* OwnerActor = GetOwner();
			if (OwnerActor->ActorHasTag("Player"))
			{
				//CastToSlasherCharacter, FlipFlopTheBoolean. 
				ASlasherCharacter* SlasherCharacter = Cast<ASlasherCharacter>(OwnerActor);
				SlasherCharacter->bShowDebugItemTrace = !SlasherCharacter->bShowDebugItemTrace;
			}
		}

		if (ImGui::Button("Toggle Debug EnemyTrace Trace"))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, "Toggle Debug Enemy Trace Not Implemented");
		}
		if (ImGui::Button("Toggle Weapon Show Debug Traces"))
		{
			USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(GetWorld()->GetGameInstance());
			if (SlasherGI != nullptr)
			{
				SlasherGI->bShowWeaponActorAttackTraceDebug = !SlasherGI->bShowWeaponActorAttackTraceDebug;
			}
		}
		
	}
	if (ImGui::CollapsingHeader("Travel Functions"))
	{
		if (ImGui::Button("TRAVEL TO - Combat"))
		{
			TravelToLevel("Combat");
		}
		if (ImGui::Button("TRAVEL TO - Movement"))
		{
			TravelToLevel("Movement");
		}
		if (ImGui::Button("TRAVEL TO - Physics"))
		{
			TravelToLevel("Physics");
		}
		if (ImGui::Button("TRAVEL TO - ItemZoo"))
		{
			TravelToLevel("ItemZoo");
		}
		if (ImGui::Button("TRAVEL TO - MainMenu"))
		{
			TravelToLevel("MainMenu");
		}
	}
	if (ImGui::CollapsingHeader("Test Ability Functions"))
	{
		static int ExpToGrant;
		static int ItemIDToEquip;
		static int AddItemIDToInv;
		static int PrimaryIDToAdd;

		static FString Disp_PrimaryEquipName = EquipItemTextDisplay_PrimaryEquipName;
		static FString EquipItemTextDisplay_Disp = EquipItemTextDisplay_PrimaryEquipDescription;
		//Amount of EXP To Add
		ImGui::TextColored(ImGui_COLOR_WHITE, "Amount of Exp to Add");
		ImGui::InputInt("EXP To Add", &ExpToGrant);
		if (ImGui::Button("Grant EXP Exp"))
		{
			DebugFunction_GrantExp(ExpToGrant);
		}

		//Equip ItemID Button
		ImGui::InputInt("ItemIDToEquip", &ItemIDToEquip);
		if (ImGui::Button("Equip Item ID"))
		{
			AActor* OwnerActor = GetOwner();

			ImGui::TextColored(ImGui_COLOR_GREEN, "Equipment Name To Equip:%s", TCHAR_TO_UTF8(*Disp_PrimaryEquipName));
			ImGui::TextColored(ImGui_COLOR_GREEN, "Result:%s", TCHAR_TO_UTF8(*EquipItemTextDisplay_Disp));
			if (OwnerActor->ActorHasTag("Player"))
			{
				ASlasherCharacter* PlayerRef = Cast<ASlasherCharacter>(OwnerActor);
				PlayerRef->EquipItemID(ItemIDToEquip);
			}
			//EquipItem -- Function needs to be built. 
		}

		//Add an Item to Inventory
		ImGui::InputInt("Item ID to Add to Inv", &AddItemIDToInv);
		if (ImGui::Button("Add Item to Inv"))
		{
			AActor* OwnerActor = GetOwner();
			if (OwnerActor->ActorHasTag("Player"))
			{
				ASlasherCharacter* PlayerRef = Cast<ASlasherCharacter>(OwnerActor);
				PlayerRef->AddItemToInventory(AddItemIDToInv);
			}
		}
		//EquipItemButton
		ImGui::InputInt("PrimaryWeaponID To Equip", &PrimaryIDToAdd);
		if (ImGui::Button("PrimaryWeaponID Equip"))
		{
			AActor* OwnerActor = GetOwner();
			if (OwnerActor->ActorHasTag("Player"))
			{
				ASlasherCharacter* PlayerRef = Cast<ASlasherCharacter>(OwnerActor);
				PlayerRef->EquipmentComponent->EquipItem_SpawnEquipMesh(0, PrimaryIDToAdd);
			}
			//EquipItem -- Function needs to be built. 
		}
	}
	if (ImGui::CollapsingHeader("Debug Character Animation"))
	{
		DebugCharacterAnimation();
	}

	ImGui::End();
}

void UAC_ImGuiActorDebug::SpawnItem(int ItemID)
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		//Actor SpawnLocations;

		const FVector PlayerForwardVector = GetOwner()->GetActorForwardVector();
		const FVector PlayerLocation = GetOwner()->GetActorLocation();
		const FVector SpawnLocation = PlayerLocation + FVector(0.0f, 0.0f, 100) + (PlayerForwardVector * 1000.0f);
		// Forward Distance to Spawn Item. 
		const FRotator SpawnRotation = GetOwner()->GetActorRotation();

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		ActorSpawnParams.bDeferConstruction = true;
		AItemActor* SpawnedItemActor = World->SpawnActor<AItemActor>(ItemClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

		if (SpawnedItemActor)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, "Spawned Actor is valid");
			SpawnedItemActor->SpawnItemID = ItemID;
			//UGameplayStatics::FinishSpawningActor(SpawnedItemActor, FTransform (SpawnLocation, SpawnRotation));
			ImGui_DrawDebugSphere(World, SpawnLocation, 100.0f, FColor::Blue, 30.0f, false);
			FTransform SpawnTransform(SpawnRotation, SpawnLocation, FVector(1.0f, 1.0f, 1.0f));
			UGameplayStatics::FinishSpawningActor(SpawnedItemActor, SpawnTransform);
		}
	}
	FString DebugMessage = FString::FromInt(ItemID);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, DebugMessage);
}

void UAC_ImGuiActorDebug::ImGui_DrawDebugSphere(UWorld* World, FVector Location, float Radius, FColor Color,
                                                float Duration, bool bPersistentLines)
{
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("Draw Debug Sphere -- ImGuiDebugActorComponent.cpp -- World Is Null"));
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
		World, // World context
		Location, // Sphere location
		Radius, // Sphere radius
		12, // Number of segments
		Color, // Sphere color
		bPersistentLines, // Persistent lines
		Duration, // Duration in seconds
		0, // Depth priority (0 = foreground)
		1.0f // Line thickness
	);
}


void UAC_ImGuiActorDebug::DebugFunction_GrantExp(float AmtToAdd)
{
	AActor* Owner = GetOwner();
	if (Owner != nullptr)
	{
		if (Owner->ActorHasTag("Player"))
		{
			ASlasherCharacter* PlayerRef = Cast<ASlasherCharacter>(Owner);
			PlayerRef->AbilityComponent->ExecuteAbilityID(1, EAbilityType::Instant, 0, 0, 0, 0, AmtToAdd, 0, 0, 0);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DebugFunction_GrantExp -- Owner is Null"));
	}
}

void UAC_ImGuiActorDebug::DebugCharacterAnimation()
{
	static constexpr ImVec4 ImGui_COLOR_RED = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Full Red
	static constexpr ImVec4 ImGui_COLOR_GREEN = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // Full Green
	static constexpr ImVec4 ImGui_COLOR_MAGENTA = ImVec4(1.0f, 0.0f, 1.0f, 1.0f); // Magenta (red + blue)

	ASlasherCharacter* PlayerRef = Cast<ASlasherCharacter>(GetOwner());
	UAnimInstance* AnimInst = PlayerRef->GetMesh()->GetAnimInstance();
	USlasherChrAnimInstance* SlasherChrAnimInst = Cast<USlasherChrAnimInstance>(AnimInst);


	if (PlayerRef)
	{
		if (SlasherChrAnimInst)
		{
			ImGui::Begin("Character Animation Debug");

			float DebugPlayerSpeed = SlasherChrAnimInst->ChrAnimInst_Speed;
			ImGui::TextColored(ImGui_COLOR_GREEN, "Float - Player Speed -- %f", DebugPlayerSpeed);

			bool Debug_bIsMoving = SlasherChrAnimInst->bChrAnimInst_IsMoving;
			ImGui::TextColored(ImGui_COLOR_RED, "Bool - Is Moving? -- %s\n", Debug_bIsMoving ? "true" : "false");

			bool Debug_IsSprinting = SlasherChrAnimInst->bChrAnimInst_IsSprinting;
			ImGui::TextColored(ImGui_COLOR_RED, "Bool - Is Sprinting? -- %s\n", Debug_IsSprinting ? "true" : "false");


			bool Debug_bIsInAir = SlasherChrAnimInst->bChrAnimInst_IsInAir;
			ImGui::TextColored(ImGui_COLOR_RED, "Bool - Is InAir? -- %s\n", Debug_bIsInAir ? "true" : "false");


			EMovementMode Debug_MovementMode = (SlasherChrAnimInst->EnumChrAnimInst_MovementMode);
			FText DebugMoveState = UEnum::GetDisplayValueAsText(Debug_MovementMode);

			ImGui::TextColored(ImGui_COLOR_MAGENTA, "Enum - Movement Mode -- %s\n",
			                   TCHAR_TO_UTF8(*DebugMoveState.ToString()));

			ImGui::End();
		}
		else
		{
			ImGui::Begin("Character Animation Debug");
			ImGui::Text("Player Animation Reference is Not valid or Not equal to Slasher Character Anim Instance/BP.");
			ImGui::Text("called from debug anim function in DebugComponent.cpp");
			ImGui::End();
		}
	}
	else
	{
		ImGui::Begin("Character Animation Debug");
		ImGui::Text("Player Ref is Null, called from debug anim function in DebugComponent.cpp");
		ImGui::End();
	}
}

void UAC_ImGuiActorDebug::DebugDisplayInventory()
{
	static constexpr ImVec4 ImGui_COLOR_RED = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Full red
	static constexpr ImVec4 ImGui_COLOR_GREEN = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // Full green
	static constexpr ImVec4 ImGui_COLOR_BLUE = ImVec4(0.0f, 0.0f, 1.0f, 1.0f); // Full blue
	static constexpr ImVec4 ImGui_COLOR_YELLOW = ImVec4(1.0f, 1.0f, 0.0f, 1.0f); // Yellow (red + green)
	static constexpr ImVec4 ImGui_COLOR_CYAN = ImVec4(0.0f, 1.0f, 1.0f, 1.0f); // Cyan (green + blue)
	static constexpr ImVec4 ImGui_COLOR_MAGENTA = ImVec4(1.0f, 0.0f, 1.0f, 1.0f); // Magenta (red + blue)
	static constexpr ImVec4 ImGui_COLOR_WHITE = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // White
	static constexpr ImVec4 ImGui_COLOR_BLACK = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // Black
	static constexpr ImVec4 ImGui_COLOR_GRAY = ImVec4(0.5f, 0.5f, 0.5f, 1.0f); // Gray
	static constexpr ImVec4 ImGui_COLOR_LIGHT_GRAY = ImVec4(0.8f, 0.8f, 0.8f, 1.0f); // Light gray
	static constexpr ImVec4 ImGui_COLOR_DARK_GRAY = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); //Dark Grey

	UWorld* World = GetWorld();
	USlasherGameInstance* SlasherGI = World->GetGameInstance<USlasherGameInstance>();

	ImGui::Begin("Player Inventory");

	for (int i = 0; i < SlasherGI->Inventory.Num(); i++)
	{
		FName RowName = FName(FString::FromInt(SlasherGI->Inventory[i]));
		FItemStruct* InvStruct = ItemDataTable->FindRow<FItemStruct>(RowName, TEXT("InventoryLookup"), false);
		if (InvStruct)
		{
			if (SlasherGI->Inventory[i] > 0)
			{
				ImGui::TextColored(ImGui_COLOR_GREEN, "Inventory Slot 00 = %d :%s", SlasherGI->Inventory[i],
				                   TCHAR_TO_UTF8(*InvStruct->ItemName));
			}
			else
			{
				ImGui::TextColored(ImGui_COLOR_WHITE, "Inventory Slot 00 = %d :%s", SlasherGI->Inventory[i],
				                   TCHAR_TO_UTF8(*InvStruct->ItemName));
			}
		}
	}
	ImGui::End();
}


//     if (ImGui::CollapsingHeader("Vehicle Variables"))
//     {
//         ImGui::TextColored(ColorGreen, "Current Engine RPM: %.1f", Debug_CurrentRPM);
//         ImGui::TextColored(ColorGreen, "Current Mapped RPM Value Pitch Modifier: %.1f", Debug_MappedPitchValue);
//         ImGui::TextColored(ColorGreen, "Current Speed MPH: %.1f", fdebug_CurrentSpeed);
//         ImGui::TextColored(ColorGreen, "Current Gear: %d", debug_CurrentGear);
//         ImGui::Text("Throttle Input: %.0f", DebugThrottleInput);
//         ImGui::Text("Brake Input: %.0f", DebugBrakeInput);
//         ImGui::Separator();
//         ImGui::TextColored(ColorRed, "FL: %s\n", bDebug_IsSkiddingWheel_00 ? "true" : "false");
//         ImGui::TextColored(ColorGreen, "FL Slip Magnitude: %.1f", fDebug_SkidMagnitude_Wheel_00);
//         ImGui::TextColored(ColorRed, "FR: %s\n", bDebug_IsSkiddingWheel_01 ? "true" : "false");
//         ImGui::TextColored(ColorGreen, "FR Slip Magnitude: %.1f", fDebug_SkidMagnitude_Wheel_01);
//         ImGui::TextColored(ColorRed, "RL: %s\n", bDebug_IsSkiddingWheel_02 ? "true" : "false");
//         ImGui::TextColored(ColorGreen, "RL Slip Magnitude : %.1f", fDebug_SkidMagnitude_Wheel_02);
//         ImGui::TextColored(ColorRed, "RR: %s\n", bDebug_IsSkiddingWheel_03 ? "true" : "false");
//         ImGui::TextColored(ColorGreen, "RR Slip Magnitude: %.1f", fDebug_SkidMagnitude_Wheel_03);
//         ImGui::Separator();
//     }
//     
//     if (ImGui::CollapsingHeader("Vehicle Replicated Variables"))
//     {
//         ImGui::TextColored(ColorBlue, "Rep_bBrakesActive?: %s\n", Rep_bBrakesActive ? "true" : "false");
//         ImGui::TextColored(ColorBlue, "Rep_bHeadlightsActive?: %s\n", Rep_bHeadLightsActive ? "true" : "false");
//         ImGui::TextColored(ColorBlue, "Rep_bHasDriver: %s\n", Rep_bHasDriver ? "true" : "false");
//         ImGui::TextColored(ColorBlue, "Rep_bEngineActive: %s\n", Rep_bEngineActive ? "true" : "false");
//
//         
//     }
//
//     if (ImGui::CollapsingHeader("Test Function Library"))
//     {
//         if (ImGui::Button("Test Headlight Toggle Client Input"))
//         {
//             ServerRPC_ToggleHeadLights();
//         }
//         if (ImGui::Button("Test Brake Light Client Input"))
//         {
//             ServerRPC_ToggleBrakeLights();
//         }
//         if (ImGui::Button("Test Engine Client Input"))
//         {
//            /* ServerRPC_ToggleEngineActive();*/
//         }
//         if (ImGui::Button("Test Has Driver Client Input"))
//         {
//             ServerRPC_ToggleHasDriver();
//         }
//         if (ImGui::Button("Start Engine Sound Debug Timer Loop - If Vehicle Pawn"))
//         {
//             DebugServerRPC_StartEngineIdleAudioLoop();
//         }
//         if (ImGui::Button("End Engine Sound Debug Timer Loop"))
//         {
//             DebugServerRPC_EndEngineIdleAudioLoop();
//         }
//
//     }
//   
//     ImGui::End();
//
// }

void UAC_ImGuiActorDebug::SaveLoadTestFunctions()
{
	static constexpr ImVec4 ImGui_COLOR_RED = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Full Red
	static constexpr ImVec4 ImGui_COLOR_GREEN = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); // Full Green
	
	ImGui::Begin("Save/Load Test Functions");
	ImGui::Text("Save/Load Test Functions");
	
	if (ImGui::Button("Save Game"))
	{
		AActor* Owner = GetOwner();
		if (Owner != nullptr && Owner->ActorHasTag("Player"))
		{
			ASlasherCharacter* PlayerRef = Cast<ASlasherCharacter>(Owner);
			FString Test = "Test";
			PlayerRef->SaveLoadComponent->SaveGame(Test);
		}
	}
	if (ImGui::Button("Load Game"))
	{
		AActor* Owner = GetOwner();
		if (Owner != nullptr && Owner->ActorHasTag("Player"))
		{
			FString Test = "Test";
			ASlasherCharacter* PlayerRef = Cast<ASlasherCharacter>(Owner);
			PlayerRef->SaveLoadComponent->LoadGame(Test);
		}
	}
	if (ImGui::Button("Load AutoSave Test"))
	{
		AActor* Owner = GetOwner();
		if (Owner != nullptr && Owner->ActorHasTag("Player"))
		{
			FString Autosave = "AutoSave";
			ASlasherCharacter* PlayerRef = Cast<ASlasherCharacter>(Owner);
			PlayerRef->SaveLoadComponent->LoadGame(Autosave);
		}
	}
	
	ImGui::End();
}
