// Copyright Epic Games, Inc. All Rights Reserved.

#include "OpenTheDoorGameMode.h"
#include "Characters/ABaseCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOpenTheDoorGameMode::AOpenTheDoorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
