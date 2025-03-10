// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ActionUseItemButton.h"

#include "Modes/SlasherGameInstance.h"
#include "Kismet/GameplayStatics.h"


/*
 *    Construction 
 */
void UActionUseItemButton::NativeConstruct()
{
	Super::NativeConstruct();
}

/*
 *    Event Visibility Changed
 */
void UActionUseItemButton::HandleNativeVisibilityChanged(ESlateVisibility InVisibility)
{
}

/*
 *    Mouse Button Down Events
 */
FReply UActionUseItemButton::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry,
                                                            const FPointerEvent& InMouseEvent)
{
	Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);


	return FReply::Unhandled();
}

FReply UActionUseItemButton::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(GetGameInstance());
	if (SlasherGI)
	{
		FString ClickedItemID = FString::FromInt(SlasherGI->GI_ClickedItemID);
		FString ClickItemInvIndex = FString::FromInt(SlasherGI->GI_ClickedItemInventoryIndex);

		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, "ClickedItemID: " + ClickedItemID);
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::White, "ClickItemInvIndex: " + ClickItemInvIndex);
	}


	return FReply::Handled();
}


/*
 *    Mouse Over Events
 */
void UActionUseItemButton::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (InventoryUIDataAsset != nullptr)
	{
		UGameplayStatics::PlaySound2D(this, InventoryUIDataAsset->WidgetMouseHoverAudio);

		ForeGroundTexture->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red,
		                                 "UseItemContextButton::NativeOnMouseEnter -- DATA ASSET IS NOT VALID");
	}
}

void UActionUseItemButton::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	ForeGroundTexture->SetVisibility(ESlateVisibility::Hidden);
}


/*
 *    OnDrag Event 
 */
void UActionUseItemButton::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                                UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}
