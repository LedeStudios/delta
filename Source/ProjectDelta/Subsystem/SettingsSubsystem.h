// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SettingsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDELTA_API USettingsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(UIMin=0.f, UIMax=1.f))
	float MouseX = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(UIMin=0.f, UIMax=1.f))
	float MouseY = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(UIMin=0.f, UIMax=1.f))
	float MusicVolume = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(UIMin=0.f, UIMax=1.f))
	float EffectVolume = 0.5f;
	
};
