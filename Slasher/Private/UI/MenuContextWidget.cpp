// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenuContextWidget.h"


//Construct Widget
void UMenuContextWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnNativeVisibilityChanged.AddUObject(this, &UMenuContextWidget::HandleNativeVisibilityChanged);
}

void UMenuContextWidget::HandleNativeVisibilityChanged(ESlateVisibility InVisibility)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, "HandleNativeVisibilityChanged");
	StatsWidget->StatsWidget_UpdateAll(); //Calls Update Function On Toggle of main Inventory
}

//OnMouseEnter -- OnMouse Leave
void UMenuContextWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	
}

void UMenuContextWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	
	Super::NativeOnMouseLeave(InMouseEvent);
	
}



//OnMouseButton DOWN
FReply UMenuContextWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	return FReply::Unhandled();
}

FReply UMenuContextWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	return FReply::Handled();
}



//Drag Detected 
void UMenuContextWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}


