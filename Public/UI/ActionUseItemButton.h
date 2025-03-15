// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEnums.h"
#include "InventoryUIDataAsset.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ActionUseItemButton.generated.h"

/**
 * 
 */
UCLASS()
class SLASHER_API UActionUseItemButton : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual FReply
	NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	                                  UDragDropOperation*& OutOperation) override;

	void HandleNativeVisibilityChanged(ESlateVisibility InVisibility);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventoryUIDataAsset* InventoryUIDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUseItemActionButtonContext ActionUseItemContext;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ActionButtonDisplayText;

	UPROPERTY(meta = (BindWidget))
	UImage* BackGroundTexture;

	UPROPERTY(meta = (BindWidget))
	UImage* ForeGroundTexture;
};
