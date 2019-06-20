// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "Projekt_2_RokGameMode.h"
#include "Projekt_2_RokCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjekt_2_RokGameMode::AProjekt_2_RokGameMode()
{
	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
}
