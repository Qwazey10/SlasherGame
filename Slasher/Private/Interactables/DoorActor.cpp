// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/DoorActor.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADoorActor::ADoorActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetSimulatePhysics(false);
}

// Called every frame
void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Tick the timeline
	if (DoorTimeline.IsPlaying())
	{
		DoorTimeline.TickTimeline(DeltaTime);
	}
}

// Called when the game starts or when spawned
void ADoorActor::BeginPlay()
{
	Super::BeginPlay();

	InitialDoorRotation = DoorMesh->GetRelativeRotation();
	FinishedDoorRotation = InitialDoorRotation + FRotator(0.f, 90.f, 0.f); // Rotate 90 degrees on Yaw


	if (DoorCurve_Float)
	{
		UpdateTimelineCallback.BindUFunction(this, FName("HandleTimelineUpdate"));
		FinishTimelineCallback.BindUFunction(this, FName("HandleTimelineFinished"));

		// Add curve to timeline and set callbacks
		DoorTimeline.AddInterpFloat(DoorCurve_Float, UpdateTimelineCallback);
		DoorTimeline.SetTimelineFinishedFunc(FinishTimelineCallback);

		// Set timeline properties
		DoorTimeline.SetLooping(false);
		DoorTimeline.SetPlayRate(1.0f);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red,"DoorActor.cpp -- BeginPlay -- DoorCurve_Float is NULL");
	}
}


// Door Interaction Timeline Functions
void ADoorActor::BPAudioEvent_OpenDoor_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Door Open Audio Implementation Function");
}

void ADoorActor::BPAudioEvent_CloseDoor_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Door Closed Audio Implementation Function");
}


void ADoorActor::HandleTimelineUpdate(float Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, FString::Printf(TEXT("Door Update %f"), Value));
	// Interpolate rotation
	FRotator NewRotation = UKismetMathLibrary::RLerp(InitialDoorRotation, FinishedDoorRotation, Value, true);
	DoorMesh->SetRelativeRotation(NewRotation);
	DoorMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bIsActive = true;
}

void ADoorActor::HandleTimelineFinished()
{
	DoorMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "Timeline finished!");
	bIsActive = false;
}


void ADoorActor::DoorInteractTrigger()
{
	if (!bIsActive)
	{
		if (bIsOpen)
		{
			CloseDoor();
		}
		else
		{
			OpenDoor();
		}
	}
}


void ADoorActor::OpenDoor()
{
	if (DoorTimeline.IsPlaying())
	{
		DoorTimeline.Stop();
	}
	DoorTimeline.PlayFromStart();
	bIsOpen = true;
	BPAudioEvent_OpenDoor();
}

void ADoorActor::CloseDoor()
{
	if (DoorTimeline.IsPlaying())
	{
		DoorTimeline.Stop();
	}
	DoorTimeline.ReverseFromEnd();
	bIsOpen = false;
	BPAudioEvent_CloseDoor();
}


//Player Interact Interface Functions 
void ADoorActor::PlayerToInteractable_InputInteractPressed_Implementation()
{
	DoorInteractTrigger();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "HELLO FROM DOOR INTERACT");
}

void ADoorActor::PlayerToInteractable_HighlightTrace_Implementation()
{
	//Maybe Deprecate -- moved function to SlasherCharacter.cpp Interact Highlight Trace Function. 
}


void ADoorActor::PlayerToInteractable_CustomDepthFilterOn_Implementation()
{
	DoorMesh->SetRenderCustomDepth(true);
	DoorMesh->SetCustomDepthStencilValue(1);
}

void ADoorActor::PlayerToInteractable_CustomDepthFilterOff_Implementation()
{
	DoorMesh->SetRenderCustomDepth(false);
	DoorMesh->SetCustomDepthStencilValue(0);
}


//Player Damage Function Interface
void ADoorActor::PlayerToEnemyInterface_Attack_Implementation(AActor* InstigatingActor, float BaseWeaponDamage, EDamageType PrimaryDamageType,float PrimaryStatusAmt, EDamageType SecondaryDamageType, float SecondaryStatusAmt)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, "I AM A DOOOOOOOOOOOOOOOR");
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, "AttackInterface Call Received");
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::FromInt(BaseWeaponDamage));
	
}


//Old Set Custom Depth Functions


//void ADoorActor::SetCustomDepthFilter_On()
//{
//UWorld* World=GetWorld();
//World->GetTimerManager().SetTimer(CustomDepthFilterOff_TimerHandle,this,  &ADoorActor::SetCustomDepthFilter_Off, 5.0f, false, 0.2f);


//DoorMesh->SetRenderCustomDepth(true);
//DoorMesh->SetCustomDepthStencilValue(1);


//}

//void ADoorActor::SetCustomDepthFilter_Off()
//{

//DoorMesh->SetRenderCustomDepth(false);
//DoorMesh->SetCustomDepthStencilValue(0);
//}
