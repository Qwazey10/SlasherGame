// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalUtils.h"

#include "Modes/SlasherGameInstance.h"


void GlobalUtils::PrintErrorString(const UWorld* World, const FString& String)
{
	const USlasherGameInstance* SlasherGI = Cast<USlasherGameInstance>(World->GetGameInstance());
	UE_LOG(LogTemp, Error, TEXT("%s"), *String);
	if (SlasherGI != nullptr && SlasherGI->bShowFatalErrorPrintString == true)
	{
		
		if (GEngine != nullptr)
		{
			
			GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, String);
			
		}
		
	}
	
}

GlobalUtils::GlobalUtils()
{
}

GlobalUtils::~GlobalUtils()
{
}
		