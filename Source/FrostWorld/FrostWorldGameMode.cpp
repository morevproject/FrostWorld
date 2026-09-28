// Copyright Epic Games, Inc. All Rights Reserved.

#include "FrostWorldGameMode.h"
#include "FrostWorldCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFrostWorldGameMode::AFrostWorldGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
