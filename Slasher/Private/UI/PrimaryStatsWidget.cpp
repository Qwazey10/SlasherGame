// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PrimaryStatsWidget.h"

#include "Character/SlasherCharacter.h"
#include "Modes/SlasherGameInstance.h"
#include "Kismet/GameplayStatics.h"


/*
 *  Constructor
 */
void UPrimaryStatsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnNativeVisibilityChanged.AddUObject(this, &UPrimaryStatsWidget::HandleNativeVisibilityChanged);
	//Define Base Text Values
	//HPTextBlock->SetText(FText::FromString("HP ITEM"));
	//MPTextBlock->SetText(FText::FromString("MP"));
	//GuardTextBlock->SetText(FText::FromString("GUARD"));
	//ExperienceTextBlock->SetText(FText::FromString("EXPERIENCE"));
	//LevelTextBlock->SetText(FText::FromString("LEVEL"));
	//StatusTextBlock->SetText(FText::FromString("STATUS"));
	//GoldTextBlock->SetText(FText::FromString("GOLD"));
}

void UPrimaryStatsWidget::HandleNativeVisibilityChanged(ESlateVisibility InVisibility)
{
	PrimaryStatsWidget_UpdateAll();
}

/*
 *  Mouse Button Down
 */
FReply UPrimaryStatsWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);

	
	return FReply::Unhandled();
}

FReply UPrimaryStatsWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	
	return FReply::Handled();
}


/*
 *  Constructor
 */
void UPrimaryStatsWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}


void UPrimaryStatsWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}


/*
 *  On Drag
 */
void UPrimaryStatsWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}



//Unique functions
void UPrimaryStatsWidget::PrimaryStatsWidget_UpdateAll()
{
	USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(GetGameInstance());
	ASlasherCharacter* PlayerCharacter = Cast<ASlasherCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (PlayerCharacter)
	{
		//Set HP
		FString DisplayHP = FString::SanitizeFloat(PlayerCharacter->CurrentHealth, 0);
		Display_HPTextBlock->SetText(FText::FromString(DisplayHP));
		//Set Mana
		FString DisplayMP = FString::SanitizeFloat(PlayerCharacter->CurrentMana, 0);
		Display_MPTextBlock->SetText(FText::FromString(DisplayMP));

		//Set Experience
		FString DisplayExp = FString::SanitizeFloat(SlasherGI->GI_CurrentExperience, 0);
		Display_ExperienceTextBlock->SetText(FText::FromString(DisplayExp));
		
		//Set Level
		FString DisplayLevel = FString::FromInt(SlasherGI->GI_CurrentLevel);
		Display_LevelTextBlock->SetText(FText::FromString(DisplayLevel));


		//Attributes
		FString DisplayStrength = FString::SanitizeFloat(PlayerCharacter->Total_Strength,0);
		Display_Strength->SetText(FText::FromString(DisplayStrength));
		
		FString DisplayStamina = FString::SanitizeFloat(PlayerCharacter->Total_Stamina,0);
		Display_StaminaTextBlock->SetText(FText::FromString(DisplayStamina));

		FString DisplayDexterity = FString::SanitizeFloat(PlayerCharacter->Total_Dexterity,0);
		Display_DexterityTextBlock->SetText(FText::FromString(DisplayDexterity));

		FString DisplayIntelligence = FString::SanitizeFloat(PlayerCharacter->Total_Intelligence,0);
		Display_Intelligence->SetText(FText::FromString(DisplayIntelligence));

		//Set Damage
		FString DisplayDamage = FString::SanitizeFloat(PlayerCharacter->Total_Damage,0);
		Display_DamageTextBlock->SetText(FText::FromString(DisplayDamage));

		FString DisplayMagicDmgMod = FString::SanitizeFloat(PlayerCharacter->Total_MagicDamageMod,0);
		Display_MagicDmgModTextBlock->SetText(FText::FromString(DisplayMagicDmgMod));

		FString DisplayAttackSpeed = FString::SanitizeFloat(PlayerCharacter->Total_AttackSpeed,0);
		Display_AttackSpeedTextBlock->SetText(FText::FromString(DisplayAttackSpeed));

		//Defensive Attributes
		FString DisplayArmor = FString::SanitizeFloat(PlayerCharacter->Total_Armor,0);
		Display_ArmorTextBlock->SetText(FText::FromString(DisplayArmor));

		FString DisplayFireResist = FString::SanitizeFloat(PlayerCharacter->Total_Resist_Fire,0);
		Display_ResistFireTextBlock->SetText(FText::FromString(DisplayFireResist));

		FString DisplayResistCold = FString::SanitizeFloat(PlayerCharacter->Total_Resist_Cold,0);
		Display_ResistColdTextBlock->SetText(FText::FromString(DisplayResistCold));

		FString DisplayDetrimental = FString::SanitizeFloat(PlayerCharacter->Total_Resist_Detrimental,0);
		Display_ResistDetrimentalTextBlock->SetText(FText::FromString(DisplayDetrimental));

		FString DisplayDivineResist = FString::SanitizeFloat(PlayerCharacter->Total_Resist_Divine,0);
		Display_ResistDivineTextBlock->SetText(FText::FromString(DisplayDivineResist));

		
		
		//SetGold
		FString DisplayGold = FString::FromInt(SlasherGI->Gold);
		Display_GoldTextBlock->SetText(FText::FromString(DisplayGold));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(0, 20.f, FColor::Red, "PrimaryStatsWidget.cpp - Player Character is NOT VALID from Stats Window Update");
		UE_LOG(LogTemp, Warning, TEXT("PrimaryStatsWidget.cpp - Player Character is NOT VALID from Stats Window Update"));
	}
}
