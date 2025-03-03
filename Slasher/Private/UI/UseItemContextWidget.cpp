// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UseItemContextWidget.h"

#include "Structs/ItemStruct.h"
#include "Modes/SlasherGameInstance.h"
#include "Components/TextBlock.h"
#include "UI/UseItemContextButton.h"


void UUseItemContextWidget::NativeConstruct()
{

	
	Super::NativeConstruct();
	OnNativeVisibilityChanged.AddUObject(this, &UUseItemContextWidget::HandleNativeVisibilityChanged);
	//BindsVisibilityChanged

	
}

void UUseItemContextWidget::HandleNativeVisibilityChanged(ESlateVisibility InVisibility)
{

	//BindsVisibilityChanged
	if (InVisibility == ESlateVisibility::Visible)
	{
		UWorld* World = GetWorld();
		USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(GetGameInstance());
		
		if (SlasherGI)
		{
			for (int i = 0; i < SlasherGI->Inventory.Num(); i++)
			{
				
				bool bFoundItemSlot = SlasherGI->Inventory[i] > 0;
				if (bFoundItemSlot)
				{
					FString ItemIDToString = FString::FromInt(SlasherGI->Inventory[i]); // Gets Current index
					FName RowName = FName(*ItemIDToString);
					FItemStruct* FoundItemStruct = SlasherGI->ItemDataTable->FindRow<FItemStruct>(RowName, "Get Row if Inventory Has Item");

					if (SlasherGI->ItemDataTable->GetRowNames().Contains(RowName))
					{
						
						if (FoundItemStruct->EquipSlot == EEquipmentSlot::UsableItem)
						{
							//UUseItemContextButton* ItemButton = CreateWidget<UUseItemContextButton>(this, UUseItemContextButton::StaticClass());
							UUserWidget* ItemButtonBase = CreateWidget<UUserWidget>(GetWorld() , ItemButtonWidgetClass);
							UUseItemContextButton* ItemButton = Cast<UUseItemContextButton>(ItemButtonBase);
							
							ItemButton->ItemID=FoundItemStruct->ItemID;
							ItemButton->OnClick_ItemIndex=i;
							ItemButton->OwnerWidgetReference = this; //Set Self as reference to created button widget. 
							ItemButton->ItemDisplayText->SetText(FText::FromString(*FoundItemStruct->ItemName));

						
							UseItemWidgetScrollBox->AddChild(ItemButton);
						}

					}
				}
				else
				{
					UE_LOG(LogTemp, Display, TEXT("NotEmptySlot Slot Found at Index: %d"), i);
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1,20, FColor::Red, "UseItemContextWidget.cpp - On Vis Change -- GameInstance is NOT VALID");
		}
	}
	if (InVisibility == ESlateVisibility::Hidden)
	{
		UseItemWidgetScrollBox->ClearChildren();
	}
}

//Mouse Enter and Leave Functions
void UUseItemContextWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	
}

void UUseItemContextWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	
	Super::NativeOnMouseLeave(InMouseEvent);
	
}
//MouseClickFunctions
FReply UUseItemContextWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	
	Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	
	return FReply::Unhandled();
}

FReply UUseItemContextWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	return FReply::Handled();
}

//Drag Functions
void UUseItemContextWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	
}

void UUseItemContextWidget::AddChildWidgetsForInventory()
{
	USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(GetGameInstance());
	if (SlasherGI)
	{
		//UseItemWidgetScrollBox->AddChild()
	}
	
}
