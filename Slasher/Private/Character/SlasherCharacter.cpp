// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/SlasherCharacter.h"
#include "ActorComponent/AC_AbilityComponent.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "ActorComponent/AC_ImGuiActorDebug.h"
#include "Structs/LevelUpStruct.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Modes/SlasherGameInstance.h"



DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

/**
 * Constructor for ASlasherCharacter.
 * Initializes default properties, components and binds timeline events for the character.
 *
 * @return ASlasherCharacter instance with initialized components and properties required for the character's functionality in the game.
 */


ASlasherCharacter::ASlasherCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	//Actor Tags
	Tags.Add(FName("Player"));
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
	//Set Up the FPP Arms Mesh
	GetMesh()->SetupAttachment(FirstPersonCameraComponent); // Sets the Inherited Mesh from Character Comp to Camera.
	GetMesh()->SetOnlyOwnerSee(true);
	GetMesh()->SetRelativeLocation(FVector(-5.0f, 0.0f, -157.0f));
	GetMesh()->CastShadow = false;
	GetMesh()->bCastDynamicShadow = false;
	

	PrimaryItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Primary Item Mesh"));
	PrimaryItemMesh->CastShadow = false;
	PrimaryItemMesh->bCastDynamicShadow = false;
	//ToDo -- Set Relevant Location/Rotation
	

	//Create Character related Components 
	DebugActorComponent = CreateDefaultSubobject<UAC_ImGuiActorDebug>(TEXT("ImGui Debug Component"));
	AbilityComponent = CreateDefaultSubobject<UAC_AbilityComponent>(TEXT("Ability Component"));
	PrimaryContextMenuManager = CreateDefaultSubobject<UAC_PrimaryContextMenuManager>(TEXT("PrimaryContextMenuManager"));
	
	//Rotating Item Static Mesh
	RotatingMenuItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rotating Menu Item Static Mesh"));
	RotatingMenuItemStaticMesh->SetupAttachment(FirstPersonCameraComponent);
	RotatingMenuItemStaticMesh->SetRenderCustomDepth(true);
	RotatingMenuItemStaticMesh->CastShadow = false;
	RotatingMenuItemStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//CrouchTimeLine - Implementation
	CrouchTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("CrouchTimeline"));
	CrouchTimeline->SetLooping(false);




}

/**
 * Called when the game starts or when the character is spawned.
 * Initializes key components, attributes, and UI elements necessary for character behavior.
 *
 * - Calls the parent class's BeginPlay method.
 * - Sets up base variables and attributes through multiple helper methods.
 * - Attaches the gun mesh to the character's skeleton, ensuring proper configuration post-construction.
 * - Adjusts visibility of different gun versions based on the usage of motion controllers.
 * - Logs debugging messages for troubleshooting during game execution.
 * - Validates the existence of the CrouchTimeline and provides a debug message if it is null.
 */
void ASlasherCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	BeginPlay_SetUpBaseVars();
	BeginPlay_SetLevel();
	BeginPlay_SetBaseAttributes();
	SetupEquipmentAttributes();
	BeginPlay_CreateInventoryWidgets();
	
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, "ASlasherCharacter::BeginPlay");
	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	//FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	//if (bUsingMotionControllers)
	//{
	//	VR_Gun->SetHiddenInGame(false, true);
	//	Mesh1P->SetHiddenInGame(true, true);
	//}
	//else
	//{//
	//	VR_Gun->SetHiddenInGame(true, true);
	//	Mesh1P->SetHiddenInGame(false, true);
	//}

	if (CrouchTimeline == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Red, "CrouchTimeline is null");
	}
	//Update Timeline Function 
	FOnTimelineFloat SetCrouchHeightTimeline;
	
	SetCrouchHeightTimeline.BindUFunction(this, FName("SetCrouchHeight"));
	
	if (PlayerDataAsset != nullptr)
	{
		CrouchTimeline->AddInterpFloat(PlayerDataAsset->CrouchCurve, SetCrouchHeightTimeline);
		CrouchTimeline->SetPlayRate(PlayerDataAsset->CrouchSpeed);
	}
	
	
	//Timeline Finished Function 
	FOnTimelineEvent SetCrouchHeightTimeline_Finished;
	
	SetCrouchHeightTimeline_Finished.BindUFunction(this, FName("OnCrouchFinished"));
	CrouchTimeline->SetTimelineFinishedFunc(SetCrouchHeightTimeline_Finished);
}

void ASlasherCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Show Player Debug Menu. 
	if (bShowPlayerDebugMenu)
	{
		DebugActorComponent->DisplayDebug_PlayerCharacter(this);   
	}

	//Show Debug Item Trace Toggle. 	
	if (bShowDebugItemTrace)
	{
		DebugItemTrace();
	}
	
	//Show Debug Enemy Trace Toggle
	if (bShowDebugEnemyTrace)
	{
		
	}
	RotatingMenuItem_SetBaseRotation(25.0f);

	InteractHighlightTrace();



	
}






//********************************* Input ***********************************************

void ASlasherCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	//Inputs
	PlayerInputComponent->BindAction("OnPress_W", IE_Pressed, this, &ASlasherCharacter::OnPress_W);
	PlayerInputComponent->BindAction("OnPress_S", IE_Pressed, this, &ASlasherCharacter::OnPress_S);
	PlayerInputComponent->BindAction("OnPress_A", IE_Pressed, this, &ASlasherCharacter::OnPress_A);
	PlayerInputComponent->BindAction("OnPress_D", IE_Pressed, this, &ASlasherCharacter::OnPress_D);

	PlayerInputComponent->BindAction("OnPress_W", IE_Released, this, &ASlasherCharacter::OnRelease_W);
	PlayerInputComponent->BindAction("OnPress_S", IE_Released, this, &ASlasherCharacter::OnRelease_S);
	PlayerInputComponent->BindAction("OnPress_A", IE_Released, this, &ASlasherCharacter::OnRelease_A);
	PlayerInputComponent->BindAction("OnPress_D", IE_Released, this, &ASlasherCharacter::OnRelease_D);
	
	//Action Inputs
	PlayerInputComponent->BindAction("OnPress_Q", IE_Pressed, this, &ASlasherCharacter::OnPress_Q);
	PlayerInputComponent->BindAction("OnPress_E", IE_Pressed, this, &ASlasherCharacter::OnPress_E);
	PlayerInputComponent->BindAction("OnPress_R", IE_Pressed, this, &ASlasherCharacter::OnPress_R);
	PlayerInputComponent->BindAction("OnPress_T", IE_Pressed, this, &ASlasherCharacter::OnPress_T);
	PlayerInputComponent->BindAction("OnPress_G", IE_Pressed, this, &ASlasherCharacter::OnPress_G);
	PlayerInputComponent->BindAction("OnPress_SHIFT", IE_Pressed, this, &ASlasherCharacter::OnPress_SHIFT);
	PlayerInputComponent->BindAction("OnPress_CTRL", IE_Pressed, this, &ASlasherCharacter::OnPress_CTRL);
	PlayerInputComponent->BindAction("OnPress_SPACE", IE_Pressed, this, &ASlasherCharacter::OnPress_SPACE);

	PlayerInputComponent->BindAction("OnPress_Q", IE_Released, this, &ASlasherCharacter::OnRelease_Q);
	PlayerInputComponent->BindAction("OnPress_E", IE_Released, this, &ASlasherCharacter::OnRelease_E);
	PlayerInputComponent->BindAction("OnPress_R", IE_Released, this, &ASlasherCharacter::OnRelease_R);
	PlayerInputComponent->BindAction("OnPress_T", IE_Released, this, &ASlasherCharacter::OnRelease_T);
	PlayerInputComponent->BindAction("OnPress_G", IE_Released, this, &ASlasherCharacter::OnRelease_G);
	PlayerInputComponent->BindAction("OnPress_SHIFT", IE_Released, this, &ASlasherCharacter::OnRelease_SHIFT);
	PlayerInputComponent->BindAction("OnPress_CTRL", IE_Released, this, &ASlasherCharacter::OnRelease_CTRL);
	PlayerInputComponent->BindAction("OnPress_SPACE", IE_Released, this, &ASlasherCharacter::OnRelease_SPACE);
	




	//Old Slasher references
	
	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	//PlayerInputComponent->BindAction("E Press", IE_Pressed, this, ASlasherCharacter::E_Press);
	//PlayerInputComponent->BindAction("E Press")
	// Bind fire event
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASlasherCharacter::OnFire);

	// Enable touchscreen input
	//EnableTouchscreenMovement(PlayerInputComponent);
	

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ASlasherCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASlasherCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASlasherCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASlasherCharacter::LookUpAtRate);
}

//************* Input Press ************

void ASlasherCharacter::OnPress_W()
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Red,"Pressed W");
	AddMovementInput(GetActorForwardVector(), 1);
	
}

void ASlasherCharacter::OnPress_S()
{
	AddMovementInput(GetActorForwardVector(), -1);
}

void ASlasherCharacter::OnPress_A()
{
	AddMovementInput(GetActorRightVector(), -1);
}

void ASlasherCharacter::OnPress_D()
{
	AddMovementInput(GetActorRightVector(), 1);
}


//************** Input Release *********
void ASlasherCharacter::OnRelease_W()
{
	
}

void ASlasherCharacter::OnRelease_A()
{
	
}

void ASlasherCharacter::OnRelease_S()
{
	
}

void ASlasherCharacter::OnRelease_D()
{
	
}


//******** Action Input Press**************
void ASlasherCharacter::OnPress_Q()
{
	bShowPlayerDebugMenu = !bShowPlayerDebugMenu;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Pressed Q registered");
}


void ASlasherCharacter::OnPress_E()
{
	InteractTrace();
	PlayerToEnemy_AttackSuccessful(6969.420);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Pressed E registered");
}

void ASlasherCharacter::OnPress_R()
{
	PrimaryContextMenuManager->OpenContextMenuKeyPressed();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Pressed R registered");
}
void ASlasherCharacter::OnPress_T()
{
	AddItemToInventory(3);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Pressed T registered");
}

void ASlasherCharacter::OnPress_G()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Pressed G registered");
}
void ASlasherCharacter::OnPress_SHIFT()
{
	StartSprint();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Pressed SHIFT registered");
}
void ASlasherCharacter::OnPress_CTRL()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Pressed CTRL registered");
	OnStartCrouch(46.0f, 0.0f);
}
void ASlasherCharacter::OnPress_SPACE()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Pressed Space registered");
}
void ASlasherCharacter::OnPress_TAB()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Pressed Tab registered");
	bShowPlayerDebugMenu = !bShowPlayerDebugMenu;
}


//********** Action Input Release ********************
void ASlasherCharacter::OnRelease_Q()
{
	
}
void ASlasherCharacter::OnRelease_E()
{
	
}
void ASlasherCharacter::OnRelease_R()
{
	
}
void ASlasherCharacter::OnRelease_T()
{
	
}
void ASlasherCharacter::OnRelease_G()
{
	
}
void ASlasherCharacter::OnRelease_SHIFT()
{
	EndSprint();
}
void ASlasherCharacter::OnRelease_CTRL()
{
	OnEndCrouch(96.0f, 0.0f);
}
void ASlasherCharacter::OnRelease_SPACE()
{
	
}
void ASlasherCharacter::OnRelease_TAB()
{
	
}

//Audio Function Implementations
void ASlasherCharacter::BPAudioEvent_LevelUpAudio_Implementation()
{
	
}

void ASlasherCharacter::BPAudioEvent_HitAudio_Implementation()
{
	
}

void ASlasherCharacter::BPAudioEvent_JumpAudio_Implementation()
{
	
}

void ASlasherCharacter::BPAudioEvent_FallAudio_Implementation()
{
	
}

void ASlasherCharacter::BPAudioEvent_BurningAudio_Implementation()
{
	
}

void ASlasherCharacter::BPAudioEvent_AttackAudio_Implementation()
{
	
}

void ASlasherCharacter::BPAudioEvent_BlockAudio_Implementation()
{
	
}

void ASlasherCharacter::BPAudioEvent_RightFootStepAudio_Implementation()
{
	
}

void ASlasherCharacter::BPAudioEvent_LeftFootStepAudio_Implementation()
{
	
}


///////// OldEvents

//void ASlasherCharacter::OnFire()
//{
//	if (PrimaryContextMenuManager->bIsMenuOpen == false)
//	{
//		// try and fire a projectile
//		if (ProjectileClass != nullptr)
//		{
//			UWorld* const World = GetWorld();
//			if (World != nullptr)
//			{
//				if (bUsingMotionControllers)
//				{
//					const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
//					const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
//					World->SpawnActor<ASlasherProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
//				}
//				else
//				{
//					const FRotator SpawnRotation = GetControlRotation();
//					// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
//					const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
//
//					//Set Spawn Collision Handling Override
//					FActorSpawnParameters ActorSpawnParams;
//					ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
//
//					// spawn the projectile at the muzzle
//					World->SpawnActor<ASlasherProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
//				}
//			}
//		}
//
//		// try and play the sound if specified
//		if (FireSound != nullptr)
//		{
//			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
//		}
//
//		// try and play a firing animation if specified
//		if (FireAnimation != nullptr)
//		{
//			// Get the animation object for the arms mesh
//			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
//			if (AnimInstance != nullptr)
//			{
//				AnimInstance->Montage_Play(FireAnimation, 1.f);
//			}
//		}
//	}
//}




//*********** BEGIN PLAY FUNCTIONS ***************
void ASlasherCharacter::BeginPlay_SetUpBaseVars()
{

	UCharacterMovementComponent* SlasherCharacterMovement = GetCharacterMovement();
	if (PlayerDataAsset)
	{
		SlasherCharacterMovement->MaxWalkSpeed = PlayerDataAsset->BaseMovementSpeed;
	}
	
	
	
}



//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void ASlasherCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
//	{
//		if (TouchItem.bIsPressed)
//		{
//			if (GetWorld() != nullptr)
//			{
//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//				if (ViewportClient != nullptr)
//				{
//					FVector MoveDelta = Location - TouchItem.Location;
//					FVector2D ScreenSize;
//					ViewportClient->GetViewportSize(ScreenSize);
//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.X * BaseTurnRate;
//						AddControllerYawInput(Value);
//					}
//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.Y * BaseTurnRate;
//						AddControllerPitchInput(Value);
//					}
//					TouchItem.Location = Location;
//				}
//				TouchItem.Location = Location;
//			}
//		}
//	}
//}

void ASlasherCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		if (PrimaryContextMenuManager->bIsMenuOpen == false)
		{
			AddMovementInput(GetActorForwardVector(), Value);
		}
		// add movement in that direction
		
	}
}

void ASlasherCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		if (PrimaryContextMenuManager->bIsMenuOpen == false)
		{
			AddMovementInput(GetActorRightVector(), Value);
		}
		// add movement in that direction
		
	}
}

void ASlasherCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASlasherCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}






//bool ASlasherCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
//{
//	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
//	{
//		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ASlasherCharacter::BeginTouch);
//		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ASlasherCharacter::EndTouch);
//
//		//Commenting this out to be more consistent with FPS BP template.
//		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ASlasherCharacter::TouchUpdate);
//		return true;
//	}
//	
//	return false;
//}


//Player To Interactable Functions
void ASlasherCharacter::InteractTrace()
{
	FVector StartPos = FirstPersonCameraComponent->GetComponentLocation();
	FVector CameraRotForwardVector = FirstPersonCameraComponent->GetComponentRotation().Vector() * PlayerDataAsset->TraceDistance;
	FVector EndPos = StartPos + CameraRotForwardVector;

	
	FHitResult DebugTrace = AbilityComponent->Utility_LineTrace(StartPos, EndPos, EDrawDebugTrace::None, PlayerDataAsset->TraceDistance, 1.0f);

	if (DebugTrace.bBlockingHit && DebugTrace.Actor->GetClass()->ImplementsInterface(UBPI_PlayerToInteractable::StaticClass()))
	{
		AActor* InteractedActor = DebugTrace.GetActor();
		IBPI_PlayerToInteractable* InteractableActor = Cast<IBPI_PlayerToInteractable>(DebugTrace.Actor);
		InteractableActor->Execute_PlayerToInteractable_InputInteractPressed(InteractedActor);
	}
}

void ASlasherCharacter::InteractHighlightTrace()
{
	
	//FVector CameraPos = FirstPersonCameraComponent->GetComponentLocation();
	//FVector CameraDir = FirstPersonCameraComponent->GetForwardVector() * 10000.0f;

	FVector StartPos = FirstPersonCameraComponent->GetComponentLocation();
	FVector CameraRotForwardVector = FirstPersonCameraComponent->GetComponentRotation().Vector() * PlayerDataAsset->TraceDistance;
	FVector EndPos = StartPos + CameraRotForwardVector;

	
	FHitResult DebugTrace = AbilityComponent->Utility_LineTrace(StartPos, EndPos, EDrawDebugTrace::None, PlayerDataAsset->TraceDistance, 1.0f);

	// Implemented the interact trace from Awakening Interact Manager, this is BP code manually converted to cpp; it works? Good enough.
	//This works by declaring Interact Hit Actor In Character.h, it defines it on SetCustomDepthOn, If it doesnt block hit or hits a different
	//Actor, it calls SetCustomDepthFilterOff. 
	if (DebugTrace.bBlockingHit)
	{
		if (DebugTrace.GetActor()!= nullptr && DebugTrace.GetActor()->GetClass()->ImplementsInterface(UBPI_PlayerToInteractable::StaticClass()))
		{
			if (InteractHitActor != nullptr)
			{
				if (InteractHitActor == DebugTrace.GetActor())
				{
					InteractHitActor = DebugTrace.GetActor();
					IBPI_PlayerToInteractable* IPTI = Cast<IBPI_PlayerToInteractable>(InteractHitActor);
					IPTI->Execute_PlayerToInteractable_CustomDepthFilterOn(InteractHitActor);
				}
				else
				{
					
					IBPI_PlayerToInteractable* IPTI = Cast<IBPI_PlayerToInteractable>(InteractHitActor);
					IPTI->Execute_PlayerToInteractable_CustomDepthFilterOff(InteractHitActor);
					InteractHitActor = DebugTrace.GetActor();
				}
			}
			else
			{
				InteractHitActor = DebugTrace.GetActor();
				IBPI_PlayerToInteractable* IPTI = Cast<IBPI_PlayerToInteractable>(InteractHitActor);
				IPTI->Execute_PlayerToInteractable_CustomDepthFilterOn(InteractHitActor);
			}
				
			
		}
		else
		{
			if (InteractHitActor != nullptr)
			{
				IBPI_PlayerToInteractable* IPTI = Cast<IBPI_PlayerToInteractable>(InteractHitActor);
				IPTI->Execute_PlayerToInteractable_CustomDepthFilterOff(InteractHitActor);
				InteractHitActor = nullptr;
			}
		
		}
	}
	else
	{
		if (InteractHitActor != nullptr)
		{
			IBPI_PlayerToInteractable* PTI = Cast<IBPI_PlayerToInteractable>(InteractHitActor);
			PTI->Execute_PlayerToInteractable_CustomDepthFilterOff(InteractHitActor);
			InteractHitActor = nullptr;
		}
	}
}

void ASlasherCharacter::PlayerToEnemy_AttackSuccessful(float HitDamage)
{
	
	FVector StartPos = FirstPersonCameraComponent->GetComponentLocation();
	FVector CameraRotForwardVector = FirstPersonCameraComponent->GetComponentRotation().Vector() * PlayerDataAsset->TraceDistance;
	FVector EndPos = StartPos + CameraRotForwardVector;

	
	FHitResult DebugTrace = AbilityComponent->Utility_LineTrace(StartPos, EndPos, EDrawDebugTrace::None, PlayerDataAsset->TraceDistance, 1.0f);

	if (DebugTrace.bBlockingHit && DebugTrace.Actor->GetClass()->ImplementsInterface(UBPI_PlayerToEnemy::StaticClass()))
	{
		AActor* InteractedActor = DebugTrace.GetActor();
		IBPI_PlayerToEnemy* InteractableActor = Cast<IBPI_PlayerToEnemy>(DebugTrace.Actor);
		InteractableActor->Execute_PlayerToEnemyInterface_Attack(InteractedActor, HitDamage);
	}
}

void ASlasherCharacter::DebugItemTrace()
{
	FVector StartPos = FirstPersonCameraComponent->GetComponentLocation();
	FVector CameraRotForwardVector = FirstPersonCameraComponent->GetComponentRotation().Vector() * 10000.0f;
	FVector EndPos = StartPos + CameraRotForwardVector;

	
	FHitResult DebugTrace = AbilityComponent->Utility_LineTrace(StartPos, EndPos, EDrawDebugTrace::None, 10000.0f, 1.0f);

	if (DebugTrace.bBlockingHit&& DebugTrace.Actor != nullptr)
	{
		DebugActorComponent->DisplayDebug_Item(&DebugTrace); // Hopefully Working LOL

	}
}

void ASlasherCharacter::AddItemToInventory(int ItemIDToAdd)
{
	//Cast to Slasher GI, Add Unique for ItemIDToAdd. 
	UWorld* World = GetWorld();
	USlasherGameInstance* SlasherGI = World->GetGameInstance<USlasherGameInstance>();
	//SlasherGI->Inventory.AddUnique(ItemIDToAdd);
	if (SlasherGI != nullptr)
	{
		for (int i = 0; i < SlasherGI->Inventory.Num(); i++)
		{
			bool bFoundEmpySlot = SlasherGI->Inventory[i] == 0;
			if (bFoundEmpySlot)
			{
				UE_LOG(LogTemp, Display, TEXT("Empty Slot Found at Index: %d"), i);
				SlasherGI->Inventory[i] = ItemIDToAdd;
				break;
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("NotEmptySlot Slot Found at Index: %d"), i);
			}
		}
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "Adding item to inventory: --" + FString::FromInt(ItemIDToAdd));
}

void ASlasherCharacter::RemoveItemFromInventory(int ItemIDToRemove)
{
	//Todo -- Remove Item From Inventory
	
}

void ASlasherCharacter::SlasherCharacter_TakeDamage(float DamageTaken)
{
	CurrentHealth = CurrentHealth-DamageTaken;
	if (CurrentHealth <= 0)
	{
		DeathOfCharacter();
	}
}

void ASlasherCharacter::DeathOfCharacter()
{
	GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Black, "DEATH OF CHARACTER");
}

void ASlasherCharacter::BeginPlay_SetLevel()// TODO - Rename this function for better clarity. Level As in EXP. 
{
	Level = 1;
	//Todo -- Set This so that the level cap caps at Some assigned level. 
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		USlasherGameInstance* SlasherGI = World->GetGameInstance<USlasherGameInstance>();
		float WorkingEXP = SlasherGI->GI_CurrentExperience;
		SlasherGI->GI_CurrentLevel = 1;
		if (WorkingEXP >= 0 && ExperienceDataTable != nullptr)
		{
			float LevelCounter = 0;


			const FString ContextString(TEXT("Experience Data Context"));
			TArray<FName> RowNames = ExperienceDataTable->GetRowNames();
        
			for (const FName& RowName : RowNames)
			{
				FLevelUpStruct* Row = ExperienceDataTable->FindRow<FLevelUpStruct>(RowName, ContextString);
				if (Row)
				{
					float ExpNeededToLevel = Row->ExperienceToNextLevel;
					if (WorkingEXP >= ExpNeededToLevel)
					{
						//WorkingEXP -= ExpNeededToLevel; //Subtracting EXP
						LevelCounter++;
					}
					else
					{
						break; // Exit the loop if not enough experience to level up
					}
				}
			}

			
			
			SlasherGI->GI_CurrentLevel += LevelCounter;
			
			
			CurrentExperience = SlasherGI->GI_CurrentExperience;
			Level = SlasherGI->GI_CurrentLevel;
			BeginPlay_SetBaseAttributes();
			SetupEquipmentAttributes();// Set the Player Pawn Level
		}
	}
}
		//Define The Base St


void ASlasherCharacter::BeginPlay_SetBaseAttributes()
{
	//Define The Base Stats
	const FString ContextString(TEXT("Experience Data Context"));
	FString SetStats = FString::FromInt(Level);
	FName RowName = FName(*SetStats);
		
		
	FLevelUpStruct* Row = ExperienceDataTable->FindRow<FLevelUpStruct>(RowName, ContextString);
	if (Row)
	{
		
		
		MaxHealth = Row->BaseHealthAtLevel + FromEquipment_Health;
		CurrentHealth = MaxHealth;
		MaxMana = Row->BaseManaAtLevel+ FromEquipment_Mana;
		CurrentMana = MaxMana;

		Base_Damage = 1.0f;
		Base_MagicDamageMod = Row->BaseMagicDmgModAtLevel;
		Base_AttackSpeed = Row->BaseAttackSpeedAtLevel;
			
		Base_Armor = Row->BaseArmorAtLevel;
		Base_Strength = Row->BaseStrengthAtLevel;
		Base_Stamina = Row->BaseStaminaAtLevel;
		Base_Dexterity = Row->BaseDexterityAtLevel;
		Base_Intelligence = Row->BaseIntelligenceAtLevel;

		Base_Resist_Fire = Row->BaseFireResistAtLevel;
		Base_Resist_Cold = Row ->BaseColdResistAtLevel;
		Base_Resist_Fire = Row->BaseFireResistAtLevel;
		Base_Resist_Detrimental = Row->BaseDetrimentalResistAtLevel;
		Base_Resist_Divine = Row->BaseDivineResistAtLevel;
		ExperienceToNextLevel = Row->ExperienceToNextLevel; // This may be a bug

		//Set the Totals on Level UP
		Total_Damage = Base_Damage + FromEquipment_Damage;
		Total_MagicDamageMod = Base_MagicDamageMod + FromEquipment_MagicDamageMod;
		Total_AttackSpeed = Base_AttackSpeed + FromEquipment_AttackSpeed;

		Total_Armor = Base_Armor + FromEquipment_Armor;
		Total_Strength = Base_Strength + FromEquipment_Strength;
		Total_Stamina = Base_Stamina + FromEquipment_Stamina;
		Total_Dexterity = Base_Dexterity + FromEquipment_Dexterity;
		Total_Intelligence = Base_Intelligence + FromEquipment_Intelligence;

		Total_Resist_Fire = Base_Resist_Fire + FromEquipment_Resist_Fire;
		Total_Resist_Cold= Base_Resist_Cold + FromEquipment_Resist_Cold;
		Total_Resist_Detrimental = Base_Resist_Detrimental + FromEquipment_Resist_Detrimental;
		Total_Resist_Divine = Base_Resist_Divine + FromEquipment_Resist_Divine;
		




		

		
		
		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			USlasherGameInstance* SlasherGI = World->GetGameInstance<USlasherGameInstance>();
			CurrentExperience = SlasherGI->GI_CurrentExperience;
			ExperienceToNextLevel = Row->ExperienceToNextLevel;	
		}
	}
}

void ASlasherCharacter::testFunc_SetBaseVars()
{
	
}

void ASlasherCharacter::testFunc_SetupEquipmentPassives() // NotFinished. 
{
	UWorld* World = GetWorld();
	USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(World->GetGameInstance());
	
	//Check Helm
//	FString Helm_00_ItemIDToString = FString::FromInt(SlasherGI->Equipment[0]);
//	FName Helm_00_RowName = FName(*Helm_00_ItemIDToString);

	for (int i = 0; i < SlasherGI->Equipment.Num(); i++)
	{
		FString ItemIDToString = FString::FromInt(SlasherGI->Equipment[i]); // Gets Current index
		FName RowName = FName(*ItemIDToString);
		if (ItemDataTable->GetRowNames().Contains(RowName))
		{
			FItemStruct* LookupItemStruct = ItemDataTable->FindRow<FItemStruct>(RowName, TEXT("Item"), true);
			if (LookupItemStruct->bHasOnEquipPassive)
			{
				SwitchOnEquipPassive(LookupItemStruct->OnEquipPassive);
			}
		}
	}
	
}

void ASlasherCharacter::SetupEquipmentAttributes()
{
	
	//Zero Out Bonuses From Equipment for 1-frame //Possible Error but will optimize later if needed. 
	FromEquipment_Health = 0;
	FromEquipment_Mana = 0;
	//Guard Not Implemented

	FromEquipment_Damage = 0;
	FromEquipment_MagicDamageMod = 0;
	FromEquipment_AttackSpeed = 0;
	
	FromEquipment_Strength = 0;
	FromEquipment_Stamina = 0;
	FromEquipment_Dexterity = 0;
	FromEquipment_Intelligence = 0;

	FromEquipment_Resist_Fire = 0;
	FromEquipment_Resist_Cold = 0;
	FromEquipment_Resist_Detrimental = 0;
	FromEquipment_Resist_Divine = 0;
	
	//Set Attributes

	Total_Strength = Base_Strength;
	Total_Stamina = Base_Stamina;
	Total_Dexterity = Base_Dexterity;
	Total_Intelligence = Base_Intelligence;
	
	Total_Resist_Fire = Base_Resist_Fire;
	Total_Resist_Cold = Base_Resist_Cold;
	Total_Resist_Detrimental = Base_Resist_Detrimental;
	Total_Resist_Divine = Base_Resist_Divine;

	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(World->GetGameInstance());
		for (int i = 0; i < SlasherGI->Equipment.Num(); i++)
		{
			FString IndexNum= FString::FromInt(i);
			FName RowName = FName(*IndexNum);
			if (ItemDataTable->GetRowNames().Contains(RowName))
			{
				//Loop Over Equipment and add stats to FromEquipment vars. 
				FItemStruct* ItemStruct =ItemDataTable->FindRow<FItemStruct>(RowName, TEXT("Item"), true);
				FromEquipment_Health += ItemStruct->Health;
				FromEquipment_Mana += ItemStruct->Mana;
				//Todo - Add Guard?
				FromEquipment_Damage += ItemStruct->Damage;
				FromEquipment_AttackSpeed += ItemStruct->AttackSpeed;
				FromEquipment_MagicDamageMod += ItemStruct->MagicDmgMod;

				FromEquipment_Strength += ItemStruct->Strength;
				FromEquipment_Stamina += ItemStruct->Stamina;
				FromEquipment_Dexterity += ItemStruct->Dexterity;
				FromEquipment_Intelligence += ItemStruct->Intelligence;

				FromEquipment_Resist_Fire += ItemStruct->Resist_Fire;
				FromEquipment_Resist_Cold += ItemStruct->Resist_Cold;
				FromEquipment_Resist_Detrimental += ItemStruct->Resist_Detrimental;
				FromEquipment_Resist_Divine += ItemStruct->Resist_Divine;
				


				
			}
		}
		//End Loop
		Total_Strength = Base_Strength + FromEquipment_Strength;
		Total_Stamina = Base_Stamina + FromEquipment_Stamina;
		Total_Dexterity = Base_Dexterity + FromEquipment_Dexterity;
		Total_Intelligence = Base_Intelligence + FromEquipment_Intelligence;

		Total_Resist_Fire = Base_Resist_Fire + FromEquipment_Resist_Fire;
		Total_Resist_Cold = Base_Resist_Cold + FromEquipment_Resist_Cold;
		Total_Resist_Detrimental = Base_Resist_Detrimental + FromEquipment_Resist_Detrimental;
		Total_Resist_Divine = Base_Resist_Divine + FromEquipment_Resist_Divine;

		
	}
}

void ASlasherCharacter::SwitchOnEquipPassive(EOnEquipPassive PassiveEffect)
{
	//Equipment Stat Zeros if needed
	// TODO - Add These Stats To Character.h and imguidebugactor.cpp to reflect new character window. 
	// Set HP Regen From Gear = 0

	//Zero Out Bonuses From Armor
	FromEquipment_Health = 0;
	FromEquipment_Mana = 0;
	//Guard Not Implemented

	FromEquipment_Damage = 0;
	FromEquipment_MagicDamageMod = 0;
	FromEquipment_AttackSpeed = 0;
	
	FromEquipment_Strength = 0;
	FromEquipment_Dexterity = 0;
	FromEquipment_Intelligence = 0;

	FromEquipment_Resist_Fire = 0;
	FromEquipment_Resist_Cold = 0;
	FromEquipment_Resist_Detrimental = 0;
	FromEquipment_Resist_Divine = 0;
	
	//Set Attributes

	Total_Strength = Base_Strength;
	Total_Stamina = Base_Stamina;
	Total_Dexterity = Base_Dexterity;
	Total_Intelligence = Base_Intelligence;
	
	Total_Resist_Fire = Base_Resist_Fire;
	Total_Resist_Cold = Base_Resist_Cold;
	Total_Resist_Detrimental = Base_Resist_Detrimental;
	Total_Resist_Divine = Base_Resist_Divine;
	
	//Set Regeneration Effects
	Total_HP_Regeneration = Base_HP_Regeneration;
	FromEquipment_HP_Regeneration = 0.0f;
	Total_MP_Regeneration = Base_MP_Regeneration;
	FromEquipment_MP_Regeneration = 0.0f;
	Total_Guard_Regeneration = Base_Guard_Regeneration;
	FromEquipment_Guard_Regeneration = 0.0f;

	

	
	
	//Boolean Sets for Passive Gear -- This is for Stop All Casting Passive 
	bCanCast = true; //This is a temp solution to correct if we unequip silence mechanic item, which will set onEquip Below.

	
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
			//AbilityDataTable
			//Todo - Add Buff Icons - Remove Buff Icons?? If I want to Have Icons
			break;
		}
	case EOnEquipPassive::HPRegeneration_Medium:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: HPRegeneration - Med"));
			//AbilityComponent->ExecuteAbilityID() -- Todo LinkToAbilityComponent
			break;
		}
	case EOnEquipPassive::HPRegeneration_Large:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: HPRegeneration - Large"));
			break;
		}
	case EOnEquipPassive::ManaRegeneration_Small:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: Mana Regen - Small"));
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
			break;
		}
	case EOnEquipPassive::MovementSpeed_Small:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: MovementSpeed - Small"));
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
			break;
		}
	case EOnEquipPassive::DrainHP_Medium:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: DrainHP_Medium"));
			break;
		}
	case EOnEquipPassive::DrainHP_Large:
		{
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: DrainHP_Large"));
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
			UE_LOG(LogTemp, Display, TEXT("SwitchOnEquipPassive: Disable All Casting"));
			break;
		}
	}//end switch


	
}


//


void ASlasherCharacter::EquipItemID(int EquippedItemID)
{
	UWorld* World = GetWorld();
	if (World)
	{
		USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(World->GetGameInstance());
		if (SlasherGI)
		{
			FString ItemIDToString = FString::FromInt(EquippedItemID);
			FName RowName = FName(*ItemIDToString);
			
			if (ItemDataTable->GetRowNames().Contains(RowName))
			{
				FItemStruct* EquippedItemRef = ItemDataTable->FindRow<FItemStruct>(RowName, TEXT("EquippedItem"));
				switch (EquippedItemRef->EquipSlot)
				{
					case EEquipmentSlot::Null:
						GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("EquippedItem: Null"));
						break;

					//Switch Statement Helm.
					case EEquipmentSlot::Helm:
						GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("EquippedItem: Helm"));
							if (SlasherGI->Equipment[0]>0)
							{
							//Slot is occupied, Add existing item to Inventory, Then Equip Item
							AddItemToInventory(EquippedItemID);
							SlasherGI->Equipment.Insert(EquippedItemID, 0);
							}
							else
							{
							//Slot is Empty, Just Add Item to Inventory 
							SlasherGI->Equipment.Insert(EquippedItemID, 0);
							}
						break;

					//Switch Statement Chest.
					case EEquipmentSlot::Chest:
						GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("EquippedItem: Chest"));
							if (SlasherGI->Equipment[1]>0)
								{
							//Slot is occupied, Add existing item to Inventory, Then Equip Item
								AddItemToInventory(EquippedItemID);
								SlasherGI->Equipment.Insert(EquippedItemID, 1);
								}
							else
								{
						//Slot is Empty, Just Add Item to Inventory 
								SlasherGI->Equipment.Insert(EquippedItemID, 1);
								}
						break;

					//Switch Statement Arms
				case EEquipmentSlot::Arms:
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("EquippedItem: Arms"));
					if (SlasherGI->Equipment[2]>0)
					{
							//Slot is occupied, Add existing item to Inventory, Then Equip Item
						AddItemToInventory(EquippedItemID);
						SlasherGI->Equipment.Insert(EquippedItemID, 2);
					}
					else
					{
						//Slot is Empty, Just Add Item to Inventory 
						SlasherGI->Equipment.Insert(EquippedItemID, 2);
					}
					break;


					//Switch Statement Legs
				case EEquipmentSlot::Legs:
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("EquippedItem: Legs"));
					if (SlasherGI->Equipment[3]>0)
					{
						//Slot is occupied, Add existing item to Inventory, Then Equip Item
						AddItemToInventory(EquippedItemID);
						SlasherGI->Equipment.Insert(EquippedItemID, 3);
					}
					else
					{
						//Slot is Empty, Just Add Item to Inventory 
						SlasherGI->Equipment.Insert(EquippedItemID, 3);
					}
					break;

					//Switch Statement Boots
				case EEquipmentSlot::Boots:
						GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("EquippedItem: Boots"));
					if (SlasherGI->Equipment[4]>0)
					{
						//Slot is occupied, Add existing item to Inventory, Then Equip Item
						AddItemToInventory(EquippedItemID);
						SlasherGI->Equipment.Insert(EquippedItemID, 4);
					}
					else
					{
						//Slot is Empty, Just Add Item to Inventory 
						SlasherGI->Equipment.Insert(EquippedItemID, 4);
					}
						break;

					//Switch Statement Ring
				case EEquipmentSlot::Ring:
						GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("EquippedItem: Ring"));
					if (SlasherGI->Equipment[5]>0)
					{
						//Slot is occupied, Add existing item to Inventory, Then Equip Item
						AddItemToInventory(EquippedItemID);
						SlasherGI->Equipment.Insert(EquippedItemID, 5);
					}
					else
					{
						//Slot is Empty, Just Add Item to Inventory 
						SlasherGI->Equipment.Insert(EquippedItemID, 5);
					}
						break;

					//Switch Statement Primary
				case EEquipmentSlot::Primary:
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("EquippedItem: Primary"));
					if (SlasherGI->Equipment[6]>0)
					{
						//Slot is occupied, Add existing item to Inventory, Then Equip Item
						AddItemToInventory(EquippedItemID);
						SlasherGI->Equipment.Insert(EquippedItemID, 6);
						EquipItem_Primary(EquippedItemID);
					}
					else
					{
						//Slot is Empty, Just Add Item to Inventory 
						SlasherGI->Equipment.Insert(EquippedItemID, 6);
						EquipItem_Primary(EquippedItemID);
					}
						break;


					//Switch Statement Secondary
				case EEquipmentSlot::Secondary:
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("EquippedItem: Secondary"));
					if (SlasherGI->Equipment[7]>0)
					{
						AddItemToInventory(EquippedItemID);
						SlasherGI->Equipment.Insert(EquippedItemID, 7);
						EquipItem_Secondary(EquippedItemID);
					}
					else
					{
						//Slot is Empty, Just Add Item to Inventory 
						SlasherGI->Equipment.Insert(EquippedItemID, 7);
						EquipItem_Secondary(EquippedItemID);
					}
						break;


					//Switch Statement UsableItem.
				case EEquipmentSlot::UsableItem:
					GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan, TEXT("EquippedItem: UsableItem"));
					if (SlasherGI->Equipment[8]>0)
					{
						AddItemToInventory(EquippedItemID);
						SlasherGI->Equipment.Insert(EquippedItemID, 8);
					}
					else
					{
						SlasherGI->Equipment.Insert(EquippedItemID, 8);
					}
					break;
				}
			}
		}
	}
}


void ASlasherCharacter::EquipItem_Primary(int PrimaryItemIDToEquip)
{
	
	FName RowName = FName(FString::FromInt(PrimaryItemIDToEquip));
	if (ItemDataTable->GetRowNames().Contains(RowName))
	{
		FItemStruct* ItemStruct = ItemDataTable->FindRow<FItemStruct>(RowName,TEXT ("PrimaryItemIDtoEquip"));
		PrimaryItemMesh->SetStaticMesh(ItemStruct->ItemDisplayMesh);
		
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("SlasherCharacter.cpp() - Equip Item ID Does not Have a Viable RowName"))
	}

	
}



void ASlasherCharacter::EquipItem_Secondary(int SecondaryItemIDToEquip)
{
 //Todo - Implement Equip Secondary once Primary is Set UP. 

	
}


//User Interface functions
void ASlasherCharacter::BeginPlay_CreateInventoryWidgets()
{
	//UWorld* World = GEngine->GetWorld();
	
}

void ASlasherCharacter::ToggleInventoryWidget()
{

}



void ASlasherCharacter::RotatingMenuItem_SetBaseRotation(float Rotation)
{
	
	if (RotatingMenuItemStaticMesh)
	{
		FRotator CurrentRotation = RotatingMenuItemStaticMesh->GetRelativeRotation();
		CurrentRotation.Yaw += Rotation * GetWorld()->GetDeltaSeconds(); // Rotation speed is determined by the `Rotation` parameter.
		RotatingMenuItemStaticMesh->SetRelativeRotation(CurrentRotation);
	}
}

void ASlasherCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	if (CapsuleComp)
	{
		CrouchTimeline->PlayFromStart();
		UCharacterMovementComponent* CharMoveComp = GetCharacterMovement();
		CharMoveComp->MaxWalkSpeed = PlayerDataAsset->CrouchMovementSpeed;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("SlasherCharacter.cpp -- Component cap is NULL"));
	}
}

void ASlasherCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	if (CapsuleComp)
	{
		CrouchTimeline->ReverseFromEnd();
		UCharacterMovementComponent* CharMoveComp = GetCharacterMovement();
		CharMoveComp->MaxWalkSpeed = PlayerDataAsset->BaseMovementSpeed;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("SlasherCharacter.cpp -- Component cap is NULL"));
	}
}

void ASlasherCharacter::SetCrouchHeight(float Alpha)
{
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	if (CapsuleComp)
	{
		float SetCapHalfHeight = FMath::Lerp(PlayerDataAsset->StandingHeight, PlayerDataAsset->CrouchHeight, Alpha);
		CapsuleComp->SetCapsuleHalfHeight(SetCapHalfHeight, false);
		
	}
}

void ASlasherCharacter::OnCrouchFinished() const
{
	DebugCharacterPrintString(FColor::Green, TEXT("OnCrouchFinished"));
}

void ASlasherCharacter::DebugCharacterPrintString(const FColor StringColor, const FString& String) const
{
	if (ShowCharacterDebugMessages == true)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, StringColor, String);
		}
	}
}

void ASlasherCharacter::DebugCharacterPrintString_Error(const FString& String) const
{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, String);
			UE_LOG(LogTemp, Error, TEXT("SlasherCharacter.cpp() - Error: %s"), *String);
		}
}


void ASlasherCharacter::FootStepLeft()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("FootStepLeft"));
}


void ASlasherCharacter::FootStepRight()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("FootStepRight"));	
}

void ASlasherCharacter::StartSprint()
{
	
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("StartSprint"));
	bIsSprinting = true;
	if (bDebug_DevSprint)
	{
		GetCharacterMovement()->MaxWalkSpeed = 2000.0f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = PlayerDataAsset->SprintSpeed;
	}
	
}

void ASlasherCharacter::EndSprint()
{
	//UMovementComponent* MovementComp = GetCharacterMovement();
	//UCharacterMovementComponent* CharMoveComp = Cast<UCharacterMovementComponent>(MovementComp);
	
	GetCharacterMovement()->MaxWalkSpeed = PlayerDataAsset->BaseMovementSpeed;
	bIsSprinting = false;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("EndSprint"));
}

//	//*
///	UWorld* World = GetWorld();
//	if (World != nullptr)
//	{
//		USlasherGameInstance* SlasherGI = World->GetGameInstance<USlasherGameInstance>();
//		float WorkingEXP = SlasherGI->CurrentExperience;
//
//		if (WorkingEXP >= 0 && ExperienceDataTable != nullptr )
//		{
//		
//		}
//	}
//
//}
//if (ItemDataTable != nullptr)
//{
//	FString ItemIDToString = FString::FromInt(SetupItemID);
//	FName RowName = FName(*ItemIDToString);
//
//	if (ItemDataTable->GetRowNames().Contains(RowName))
//	{
//		UE_LOG(LogTemp, Warning, TEXT("( ItemActor.cpp -- BeginPlay_Setup() -- Item Data Table Row Found"));
//		FItemStruct* LookupItemStruct = ItemDataTable->FindRow<FItemStruct>(RowName, TEXT("Item"), true);
//		*/