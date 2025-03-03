// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryUIDataAsset.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "UseItemContextButton.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class SLASHER_API UUseItemContextButton : public UUserWidget
{
	GENERATED_BODY()

	


	
	virtual FReply NativeOnPreviewMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;

	virtual void NativeConstruct() override;
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	void HandleNativeVisibilityChanged(ESlateVisibility InVisibility);

	public:

	void SetSelected_Off();
	void SetSelected_On();
	void SetItemRotationMesh();
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "MenuContext")
	UInventoryUIDataAsset* UIDataAsset;



	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemDisplayText;
	
	UPROPERTY(meta = (BindWidget))
	UImage* ItemDisplayBackgroundImage;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemDisplaySelectedImage;
	
	UPROPERTY(meta = (BindWidget))
	UImage* ItemDisplayForegroundImage;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite);
	int ItemID;
	//This Var is set on creation  of button widget in UseItemContextWindow loop.
	UPROPERTY(EditAnywhere,BlueprintReadWrite);
	int OnClick_ItemIndex;

	//booleans. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSelected =false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHovered =false;

	UPROPERTY()
	UUserWidget* OwnerWidgetReference;
};
