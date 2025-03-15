// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/AC_PrimaryContextMenuManager.h"

#include "Character/SlasherCharacter.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UAC_PrimaryContextMenuManager::UAC_PrimaryContextMenuManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_PrimaryContextMenuManager::BeginPlay()
{
	Super::BeginPlay();

	//Create Widgets


	PrimaryMenuWidget = CreateWidget<UUserWidget>(GetWorld(), PrimaryMenuWidgetClass);

	UseItemMenuWidget = CreateWidget<UUserWidget>(GetWorld(), UseItemWidgetClass);

	UseMagicMenuWidget = CreateWidget<UUserWidget>(GetWorld(), UseMagicWidgetClass);

	EquipmentMenuWidget = CreateWidget<UUserWidget>(GetWorld(), EquipmentWidgetClass);

	CompleteStatsWidget = CreateWidget<UUserWidget>(GetWorld(), StatsWidgetClass);

	OptionsWidget = CreateWidget<UUserWidget>(GetWorld(), OptionsWidgetClass);

	bIsMenuOpen = false;

	if (PrimaryMenuWidget)
	{
		PrimaryMenuWidget->SetVisibility(ESlateVisibility::Hidden); // Visible, Hidden to toggle
		PrimaryMenuWidget->AddToViewport();
	}
	if (UseItemMenuWidget)
	{
		UseItemMenuWidget->SetVisibility(ESlateVisibility::Hidden); // Visible, Hidden to toggle
		UseItemMenuWidget->AddToViewport();
	}
	if (UseMagicMenuWidget)
	{
		UseMagicMenuWidget->SetVisibility(ESlateVisibility::Hidden); // Visible, Hidden to toggle
		UseMagicMenuWidget->AddToViewport();
	}
	if (EquipmentMenuWidget)
	{
		EquipmentMenuWidget->SetVisibility(ESlateVisibility::Hidden); // Visible, Hidden to toggle
		EquipmentMenuWidget->AddToViewport();
	}
	if (CompleteStatsWidget)
	{
		CompleteStatsWidget->SetVisibility(ESlateVisibility::Hidden); // Visible, Hidden to toggle
		CompleteStatsWidget->AddToViewport();
	}
	if (OptionsWidget)
	{
		OptionsWidget->SetVisibility(ESlateVisibility::Hidden); // Visible, Hidden to toggle
		OptionsWidget->AddToViewport();
		bIsMenuOpen = false;
	}
}


// Called every frame
void UAC_PrimaryContextMenuManager::TickComponent(float DeltaTime, ELevelTick TickType,
                                                  FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_PrimaryContextMenuManager::OpenContextMenuKeyPressed()
{
	APlayerController* PlayerCont = GetWorld()->GetFirstPlayerController();
	if (bIsMenuOpen)
	{
		ACContextMenu_InventoryContext = EInventoryContext::None;
		PlayerCont->SetShowMouseCursor(false);

		//Hide All Widgets
		PrimaryMenuWidget->SetVisibility(ESlateVisibility::Hidden);
		UseItemMenuWidget->SetVisibility(ESlateVisibility::Hidden);
		UseMagicMenuWidget->SetVisibility(ESlateVisibility::Hidden);
		EquipmentMenuWidget->SetVisibility(ESlateVisibility::Hidden);
		CompleteStatsWidget->SetVisibility(ESlateVisibility::Hidden);
		OptionsWidget->SetVisibility(ESlateVisibility::Hidden);

		bIsMenuOpen = false;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerCont);
		ClearItemRotationMesh();
	}
	else
	{
		ACContextMenu_InventoryContext = EInventoryContext::BaseMenuContext;
		PlayerCont->SetShowMouseCursor(true);

		PrimaryMenuWidget->SetVisibility(ESlateVisibility::Visible);


		bIsMenuOpen = true;
		UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerCont, PrimaryMenuWidget);
	}
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, "OpenContextMenuKeyPressed");
}


void UAC_PrimaryContextMenuManager::ClearItemRotationMesh()
{
	if (GetOwner()->ActorHasTag("Player"))
	{
		ASlasherCharacter* PlayerCharacter = Cast<ASlasherCharacter>(GetOwner());
		if (PlayerCharacter)
		{
			if (PlayerCharacter->RotatingMenuItemStaticMesh)
			{
				PlayerCharacter->RotatingMenuItemStaticMesh->SetVisibility(false);
			}
		}
	}
}
