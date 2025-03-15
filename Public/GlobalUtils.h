// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEnums.h"

/**
 * 
 */
class SLASHER_API GlobalUtils
{
	GlobalUtils();
	~GlobalUtils();
	
public:

	//Print a Fatal Error String to Log and Screen. 
	static void PrintErrorString(const UWorld* World, const FString& String);
	

	



	

};
