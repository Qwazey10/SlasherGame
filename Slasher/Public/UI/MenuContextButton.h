// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEnums.h"
#include "InventoryUIDataAsset.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MenuContextButton.generated.h"

/**
 * 
 */
UCLASS()
class SLASHER_API UMenuContextButton : public UUserWidget
{
	GENERATED_BODY()
protected:
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MenuDisplayText;
	

	UPROPERTY(meta = (BindWidget))
	UImage* BackGroundTexture;

	UPROPERTY(meta = (BindWidget))
	UImage* ForeGroundTexture;
	
	
	virtual FReply NativeOnPreviewMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;

	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	public:
	//Enum to Determine Display Text, Display text set in .cpp file.
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "MenuContext")
	EInventoryContext PrimaryMenuButton_InventoryMenuContext;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "MenuContext")
	UInventoryUIDataAsset* UIDataAsset;
	
};
