// Copyright Lede Studios. All Rights Reserved.

#include "ProjectDeltaGameMode.h"
#include "ProjectDeltaCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectDeltaGameMode::AProjectDeltaGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
