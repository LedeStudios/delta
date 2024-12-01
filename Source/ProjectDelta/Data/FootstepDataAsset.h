// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Sound/SoundCue.h"
#include "FootstepDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FFootstepSound
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UPhysicalMaterial> PhysicalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundCue> WalkSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundCue> RunSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundCue> JumpSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundCue> LandSound;
};

USTRUCT(BlueprintType)
struct FFootstepCameraShake
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCameraShakeBase> WalkCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCameraShakeBase> RunCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCameraShakeBase> JumpCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCameraShakeBase> LandCameraShake;
	
};

UCLASS(BlueprintType)
class PROJECTDELTA_API UFootstepDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FFootstepSound> FootstepSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFootstepCameraShake FootstepCameraShake;
	
public:
	FFootstepSound GetFootstepSoundByType(const UPhysicalMaterial* InType);
	
};
