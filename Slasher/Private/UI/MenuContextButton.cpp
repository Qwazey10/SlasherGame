// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenuContextButton.h"

#include "Character/SlasherCharacter.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

//#include "Components/TextBlock.h"

void UMenuContextButton::NativeConstruct()
{
	Super::NativeConstruct();
	
	// SETUP DISPLAY TEXT
	switch (PrimaryMenuButton_InventoryMenuContext)
	{
	default:
		break;
		
	case EInventoryContext::UseItem:
	{	
		MenuDisplayText->SetText(FText::FromString("USE ITEM"));

		break;
	}
	case EInventoryContext::UseMagic:
		{
			
			
			MenuDisplayText->SetText(FText::FromString("USE MAGIC"));
			break;
		}	
	case EInventoryContext::Equipment:
		{
			MenuDisplayText->SetText(FText::FromString("EQUIPMENT"));
			break;
		}
		
		
	case EInventoryContext::Stats:
		{
			MenuDisplayText->SetText(FText::FromString("STATS"));
			break;
		}
		

	case EInventoryContext::DropItem:
		{
			MenuDisplayText->SetText(FText::FromString("DROP ITEM"));
			break;
		}
		
		
	case EInventoryContext::Options:
		{
			MenuDisplayText->SetText(FText::FromString("OPTIONS"));
			break;
		}
		
	case EInventoryContext::ReturnExit:
		{
			MenuDisplayText->SetText(FText::FromString("EXIT"));
			break;
		}
		
	}
	
}


//OverRideFunctions
void UMenuContextButton::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	if (UIDataAsset != nullptr)
	{
		UGameplayStatics::PlaySound2D(this, UIDataAsset->WidgetMouseHoverAudio);
		
		ForeGroundTexture->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, "MenuContextButton::NativeOnMouseEnter -- DATA ASSET IS NOT VALID");
	}
	
}

void UMenuContextButton::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	
	Super::NativeOnMouseLeave(InMouseEvent);
	
	ForeGroundTexture->SetVisibility(ESlateVisibility::Hidden);
	
}


//MouseButtonDown
FReply UMenuContextButton::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	
	//FText MouseKeyName = InMouseEvent.ToText();
	//FString MouseKey = "MouseKeyPRESS" + MouseKeyName.ToString();
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Hello From Mouse  PREVIEW Key Press");

	return FReply::Unhandled();
	
}

FReply UMenuContextButton::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	
	FString EnumName = UEnum::GetValueAsString(PrimaryMenuButton_InventoryMenuContext);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Emerald, EnumName);

	ASlasherCharacter* PlayerCharacter = Cast<ASlasherCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	
	
	if (PlayerCharacter != nullptr)
	{
		switch (PrimaryMenuButton_InventoryMenuContext)
		{
		default:
			{
				break;
			}
		
		
		case EInventoryContext::UseItem:
			{	
				PlayerCharacter->PrimaryContextMenuManager->PrimaryMenuWidget->SetVisibility(ESlateVisibility::Hidden); // Set Primary Menu to Hidden
				PlayerCharacter->PrimaryContextMenuManager->ACContextMenu_InventoryContext=EInventoryContext::UseItem; //Set the AC MenuManager enum value to context
				PlayerCharacter->PrimaryContextMenuManager->UseItemMenuWidget->SetVisibility(ESlateVisibility::Visible);
				break;
			}
		case EInventoryContext::UseMagic:
			{
			
				PlayerCharacter->PrimaryContextMenuManager->PrimaryMenuWidget->SetVisibility(ESlateVisibility::Hidden); // Set Primary Menu to Hidden
				PlayerCharacter->PrimaryContextMenuManager->ACContextMenu_InventoryContext=EInventoryContext::UseMagic; //Set the AC MenuManager enum value to context
				PlayerCharacter->PrimaryContextMenuManager->UseMagicMenuWidget->SetVisibility(ESlateVisibility::Visible);
			
				break;
			}	
		case EInventoryContext::Equipment:
			{
				PlayerCharacter->PrimaryContextMenuManager->PrimaryMenuWidget->SetVisibility(ESlateVisibility::Hidden); // Set Primary Menu to Hidden
				PlayerCharacter->PrimaryContextMenuManager->ACContextMenu_InventoryContext=EInventoryContext::Equipment; //Set the AC MenuManager enum value to context
				PlayerCharacter->PrimaryContextMenuManager->EquipmentMenuWidget->SetVisibility(ESlateVisibility::Visible);
				break;
			}
		
		
		case EInventoryContext::Stats:
			{
				PlayerCharacter->PrimaryContextMenuManager->PrimaryMenuWidget->SetVisibility(ESlateVisibility::Hidden); // Set Primary Menu to Hidden
				PlayerCharacter->PrimaryContextMenuManager->ACContextMenu_InventoryContext=EInventoryContext::Stats; //Set the AC MenuManager enum value to context
				PlayerCharacter->PrimaryContextMenuManager->CompleteStatsWidget->SetVisibility(ESlateVisibility::Visible);
				break;
			}
		

		case EInventoryContext::DropItem:
			{
				PlayerCharacter->PrimaryContextMenuManager->PrimaryMenuWidget->SetVisibility(ESlateVisibility::Hidden); // Set Primary Menu to Hidden
				PlayerCharacter->PrimaryContextMenuManager->ACContextMenu_InventoryContext=EInventoryContext::DropItem; //Set the AC MenuManager enum value to context
				//PlayerCharacter->PrimaryContextMenuManager->DropItemMenuWidget->SetVisibility(ESlateVisibility::Visible);
				GEngine->AddOnScreenDebugMessage(-1,25,FColor::Red, "MenuContextButton.cpp -- DROP ITEM NOT IMPLEMENTED, Potential Code Commented");
				break;
			}
		
		
		case EInventoryContext::Options:
			{
				PlayerCharacter->PrimaryContextMenuManager->PrimaryMenuWidget->SetVisibility(ESlateVisibility::Hidden); // Set Primary Menu to Hidden
				PlayerCharacter->PrimaryContextMenuManager->ACContextMenu_InventoryContext=EInventoryContext::Options; //Set the AC MenuManager enum value to context
				PlayerCharacter->PrimaryContextMenuManager->OptionsWidget->SetVisibility(ESlateVisibility::Visible);
				break;
			}
		
		case EInventoryContext::ReturnExit:
			{
				PlayerCharacter->PrimaryContextMenuManager->ACContextMenu_InventoryContext = EInventoryContext::None;
				PlayerCharacter->PrimaryContextMenuManager->PrimaryMenuWidget->SetVisibility(ESlateVisibility::Hidden);
				PlayerCharacter->PrimaryContextMenuManager->bIsMenuOpen=false;
				APlayerController* PlayerCont = GetWorld()->GetFirstPlayerController();
				PlayerCont->SetShowMouseCursor(false);
				UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerCont);
				break;
			}
		
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,20,FColor::Red, "MENU CONTEXT BUTTON.cpp, Character REFERENCE is INVALID for ON PRESS");	
		}
	}

	return FReply::Handled();
	
}












void UMenuContextButton::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	
}



//ExampleButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("MyButtonName")); // The second parameter is the name and is optional.
//ExampleButton->OnClicked.AddDynamic(this, &MyUserWidget::OnButtonClicked); // Example click binding.
//RootWidget->AddChild(ExampleButton);