// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEnums.h"
#include "Components/ActorComponent.h"
#include "UI/EquipmentContextWidget.h"
#include "UI/MenuContextWidget.h"
#include "UI/OptionsWidget.h"
#include "UI/PrimaryStatsWidget.h"
#include "UI/UseItemContextWidget.h"
#include "UI/UseMagicContextWidget.h"
#include "AC_PrimaryContextMenuManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLASHER_API UAC_PrimaryContextMenuManager : public UActorComponent
{
	GENERATED_BODY()

public:

	
	//User Interface Related
	UPROPERTY()
	UUserWidget* PrimaryMenuWidget;
	
	UPROPERTY()
	UUserWidget* UseItemMenuWidget;
	
	UPROPERTY()
	UUserWidget* UseMagicMenuWidget;
	
	UPROPERTY()
	UUserWidget* EquipmentMenuWidget;
	
	UPROPERTY()
	UUserWidget* CompleteStatsWidget;
	
	UPROPERTY()
	UUserWidget* OptionsWidget;



	//Widget Class Declarations
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")
	TSubclassOf<UUserWidget> PrimaryMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")
	TSubclassOf<UUserWidget> UseItemWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")
	TSubclassOf<UUserWidget> UseMagicWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")
	TSubclassOf<UUserWidget> EquipmentWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")
	TSubclassOf<UUserWidget> StatsWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")
	TSubclassOf<UUserWidget> OptionsWidgetClass;

	TArray<UUserWidget> PrimaryMenuWidgets;


	//Vars
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "User Interface")
	bool bIsMenuOpen = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RunTime Attributes")
	EInventoryContext ACContextMenu_InventoryContext = EInventoryContext::None;
	


	
	// Sets default values for this component's properties
	UAC_PrimaryContextMenuManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenContextMenuKeyPressed();
	void ClearItemRotationMesh();
};
