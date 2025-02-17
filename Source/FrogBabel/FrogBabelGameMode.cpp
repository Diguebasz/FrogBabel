// Copyright Epic Games, Inc. All Rights Reserved.

#include "FrogBabelGameMode.h"
#include "FrogBabelCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFrogBabelGameMode::AFrogBabelGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
