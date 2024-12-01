// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayGameMode.generated.h"

class ULevelLoaderComponent;
/**
 * 
 */
UCLASS()
class PROJECTDELTA_API AGameplayGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameplayGameMode();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="LevelLoader")
	TObjectPtr<ULevelLoaderComponent> LevelLoaderComponent;
	
};
