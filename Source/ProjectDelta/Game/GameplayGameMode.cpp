// Copyright Lede Studios. All Rights Reserved.


#include "GameplayGameMode.h"

#include "ActorComponent/LevelLoaderComponent.h"

AGameplayGameMode::AGameplayGameMode()
{
	LevelLoaderComponent = CreateDefaultSubobject<ULevelLoaderComponent>("LevelLoader");
}
