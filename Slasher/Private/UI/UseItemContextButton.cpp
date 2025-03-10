// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/UseItemContextButton.h"

#include "SGraphPinDataTableRowName.h"
#include "Character/SlasherCharacter.h"
#include "Modes/SlasherGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UI/UseItemContextWidget.h"


void UUseItemContextButton::NativeConstruct()
{
	Super::NativeConstruct();
	OnNativeVisibilityChanged.AddUObject(this, &UUseItemContextButton::HandleNativeVisibilityChanged);
}


void UUseItemContextButton::HandleNativeVisibilityChanged(ESlateVisibility InVisibility)
{
	if (InVisibility == ESlateVisibility::Hidden)
	{
		this->RemoveFromParent();
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Magenta,
		                                 "UseItemContextButton.cpp::HandleNativeVisibilityChanged -- Hidden");
	}
}


//MouseButton Down
FReply UUseItemContextButton::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry,
                                                             const FPointerEvent& InMouseEvent)
{
	Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);

	return FReply::Unhandled();
}

FReply UUseItemContextButton::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(GetGameInstance());

	if (SlasherGI)
	{
		SetSelected_On();
		SetItemRotationMesh();
		if (SlasherGI->UseItemContextWidget != this)
		{
			UUseItemContextButton* PrevSelectedButton = Cast<UUseItemContextButton>(SlasherGI->UseItemContextWidget);
			if (PrevSelectedButton)
			{
				PrevSelectedButton->SetSelected_Off();
			}
			SlasherGI->UseItemContextWidget = this;
		}
		else
		{
			SlasherGI->UseItemContextWidget = this;
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red,
		                                 "UseItemContextButton.cpp::NativeOnMouseButtonDown -- SlasherGI is NULL");
	}

	return FReply::Handled();
}

void UUseItemContextButton::SetSelected_Off()
{
	bIsSelected = false;
	ItemDisplaySelectedImage->SetVisibility(ESlateVisibility::Hidden);
}

void UUseItemContextButton::SetSelected_On()
{
	USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(GetGameInstance());
	if (SlasherGI)
	{
		SlasherGI->GI_ClickedItemInventoryIndex = OnClick_ItemIndex;
		SlasherGI->GI_ClickedItemID = ItemID;
		bIsSelected = true;
	}
	ItemDisplaySelectedImage->SetVisibility(ESlateVisibility::Visible);
	ItemDisplayForegroundImage->SetVisibility(ESlateVisibility::Hidden);
}


void UUseItemContextButton::SetItemRotationMesh()
{
	USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(GetGameInstance());
	ASlasherCharacter* PlayerChar = Cast<ASlasherCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (PlayerChar && SlasherGI)
	{
		FName RowName = FName(*FString::FromInt(ItemID));
		if (SlasherGI->ItemDataTable->GetRowNames().Contains(RowName))
		{
			FItemStruct* ItemStruct = SlasherGI->ItemDataTable->FindRow<FItemStruct>(
				RowName, TEXT("Get Row if Inventory Has Item"));
			if (ItemStruct->ItemDisplayMesh != nullptr)
			{
				PlayerChar->RotatingMenuItemStaticMesh->SetVisibility(true);
				PlayerChar->RotatingMenuItemStaticMesh->SetStaticMesh(ItemStruct->ItemDisplayMesh);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red,
				                                 "UseItemContextButton.cpp::SetItemRotationMesh -- ItemDisplayMesh is NULL");
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red,
			                                 "UseItemContextButton.cpp::SetItemRotationMesh -- ItemID Does not Have a Viable RowName");
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red,
		                                 "UseItemContextButton.cpp::SetItemRotationMesh -- PlayerChar is NULL");
	}
}

//Mouse Leave and Enter
void UUseItemContextButton::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	if (UIDataAsset)
	{
		if (bIsSelected == false)
		{
			UGameplayStatics::PlaySound2D(this, UIDataAsset->WidgetMouseHoverAudio);
			ItemDisplayForegroundImage->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UUseItemContextButton::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	if (bIsSelected == false)
	{
		ItemDisplayForegroundImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

//Drag Detected
void UUseItemContextButton::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                                 UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}
