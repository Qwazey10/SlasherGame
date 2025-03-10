// Copyright Epic Games, Inc. All Rights Reserved.

#include "Modes/SlasherGameMode.h"
#include "SlasherHUD.h"
//#include "Character/SlasherCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASlasherGameMode::ASlasherGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/SlasherCharacter/BP_SlasherCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASlasherHUD::StaticClass();
}
