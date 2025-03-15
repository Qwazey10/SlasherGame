// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WeaponActor.h"

#include "Camera/CameraComponent.h"
#include "Character/SlasherCharacter.h"
#include "Interfaces/BPI_PlayerToEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Modes/SlasherGameInstance.h"
#include "Structs/ItemStruct.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	//Set Physics
	Mesh->SetSimulatePhysics(false); //Enable Simulate Physics
	Mesh->SetNotifyRigidBodyCollision(false); // Required to fire the hit event
	Mesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Mesh->bCastDynamicShadow = false;
	Mesh->CastShadow = false;

}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	OnConstruct_SetupAppearanceAndAttributes(WeaponID);
	
	
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	
	
}

void AWeaponActor::OnConstruct_SetupAppearanceAndAttributes(int ItemID)
{
	if (ItemDataTable != nullptr)
	{
		FString WeaponIDToString = FString::FromInt(ItemID);
		FName RowName = FName(*WeaponIDToString);

		if ((ItemDataTable->GetRowNames().Contains(RowName)))
		{
			FItemStruct* LookupItemStruct = (ItemDataTable->FindRow<FItemStruct>(RowName, TEXT("Item"), true));
			
			if (LookupItemStruct->ItemDisplayMesh != nullptr)
			{
				WeaponActorDamage = LookupItemStruct->Damage; // Weapon Damage
				
				PrimaryDamageType = LookupItemStruct->WeaponDamageType_Primary; //Primary Status Type
				SecondaryDamageType = LookupItemStruct->WeaponDamageType_Secondary; //Secondary Status Type

				PrimaryDamageStatusAmt = LookupItemStruct->PrimaryStatusModAmt; //Primary Status Mod Amount
				SecondaryDamageStatusAmt = LookupItemStruct->SecondaryStatusModAmt; //Secondary Status Mod Amount
				
				Mesh->SetStaticMesh(LookupItemStruct->ItemDisplayMesh); //Set Mesh From DT_Item
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, TEXT("WeaponActor.cpp -- OnConstruction() -- Item Display Mesh is not valid!"));
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, "WeaponActor.cpp -- OnConstruction() -- ItemID Not Found in ItemDataTable");
			Destroy();
		}
	}
}

/**
 * @brief Performs a trace for attacking mechanics.
 *
 * This method is responsible for executing an attack trace, typically used
 * to handle hit detection or collision during an attack. It does not take
 * any arguments or return any values. The implementation details are to be
 * provided as per specific*/



void AWeaponActor::AttackTrace()
{
	//AActor* Owner = GetOwner();
	ASlasherCharacter* PlayerCharacter = Cast<ASlasherCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (IsValid(PlayerCharacter))
	{
		USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(GetWorld()->GetGameInstance());
	
		FVector StartPos = PlayerCharacter->FirstPersonCameraComponent->GetComponentLocation();
		FVector CameraRotationForwardVector = PlayerCharacter->FirstPersonCameraComponent->GetComponentRotation().Vector() * 10000.0f;
		FVector EndPos = StartPos + CameraRotationForwardVector;
		
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(PlayerCharacter);
		ActorsToIgnore.Add(this);
		
		FHitResult HitResult;
		
		
		ETraceTypeQuery TraceType = ETraceTypeQuery::TraceTypeQuery1;
		float TraceRadius = 25.0f;

		
		EDrawDebugTrace::Type DrawDebugType = SlasherGI->bShowWeaponActorAttackTraceDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;
			
		FColor TraceColor = FColor::Red;
		FColor TraceHitColor = FColor::Green;
		float LifeTime = 5.0f;
		
		bool bHit =	UKismetSystemLibrary::SphereTraceSingle(
			GetWorld(),
			StartPos,
			EndPos,
			TraceRadius,
			TraceType,
			true,
			ActorsToIgnore,
			DrawDebugType,
			HitResult,
			false,
			TraceColor,
			TraceHitColor,
			LifeTime);
			
			
		

		if (bHit && HitResult.Actor != nullptr && HitResult.Actor->GetClass()->ImplementsInterface(UBPI_PlayerToEnemy::StaticClass()))
		{
		
			AActor* InteractedActor = HitResult.GetActor();
			IBPI_PlayerToEnemy* InteractableActor = Cast<IBPI_PlayerToEnemy>(HitResult.Actor);
			InteractableActor->Execute_PlayerToEnemyInterface_Attack(InteractedActor, GetOwner(), WeaponActorDamage,PrimaryDamageType, PrimaryDamageStatusAmt, SecondaryDamageType, SecondaryDamageStatusAmt);
		
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, "WeaponActor.cpp -- Attack Trace -- PlayerCharacter Ref is NOT VALID");
	}
	
}
//	bool UKismetSystemLibrary::SphereTraceSingle(const UObject* WorldContextObject, const FVector Start, const FVector End, float Radius, ETraceTypeQuery TraceChannel, bool bTraceComplex, const TArray<AActor*>& ActorsToIgnore, EDrawDebugTrace::Type DrawDebugType, FHitResult& OutHit, bool bIgnoreSelf, FLinearColor TraceColor, FLinearColor TraceHitColor, float DrawTime)
//
//		ECollisionChannel CollisionChannel = UEngineTypes::ConvertToCollisionChannel(TraceChannel);
//
//		static const FName SphereTraceSingleName(TEXT("SphereTraceSingle"));
//		FCollisionQueryParams Params = ConfigureCollisionParams(SphereTraceSingleName, bTraceComplex, ActorsToIgnore, bIgnoreSelf, WorldContextObject);
//
//		UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
//		bool const bHit = World ? World->SweepSingleByChannel(OutHit, Start, End, FQuat::Identity, CollisionChannel, FCollisionShape::MakeSphere(Radius), Params) : false;
//
//#if ENABLE_DRAW_DEBUG
//		DrawDebugSphereTraceSingle(World, Start, End, Radius, DrawDebugType, bHit, OutHit, TraceColor, TraceHitColor, DrawTime);
//#endif

//return bHit;
//}