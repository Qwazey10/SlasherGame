// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"
#include "UseItemContextWidget.generated.h"

/**
 * 
 */
UCLASS()
class SLASHER_API UUseItemContextWidget : public UUserWidget
{
	GENERATED_BODY()


	

	virtual FReply NativeOnPreviewMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	virtual FReply NativeOnMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;

	virtual void NativeConstruct() override;
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	void HandleNativeVisibilityChanged(ESlateVisibility InVisibility);

	void AddChildWidgetsForInventory();

	public:

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")
	TSubclassOf<UUserWidget> ItemButtonWidgetClass;

	UPROPERTY (meta=(BindWidget))
	UScrollBox* UseItemWidgetScrollBox;

	UPROPERTY (meta=(BindWidget))
	UVerticalBox* UseItemActionWidgets;
	
	
};
