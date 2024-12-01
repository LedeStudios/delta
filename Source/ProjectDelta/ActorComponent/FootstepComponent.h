// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "FootstepComponent.generated.h"


class AGameplayPlayerController;
class AGameplayPlayerCharacter;
class UTimelineComponent;
struct FFootstepSound;
class UFootstepDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTDELTA_API UFootstepComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFootstepComponent();

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	TWeakObjectPtr<AGameplayPlayerCharacter> Owner;
	TWeakObjectPtr<AGameplayPlayerController> OwnerController;

protected:
	FTimeline FootstepTimeline;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Footstep")
	float MovementSpeed = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Footstep")
	TObjectPtr<UCurveFloat> CurveFloat;

public:
	void SetMovementSpeed(const float InSpeed);

	float GetMovementSpeed() const;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Footstep")
	TObjectPtr<UFootstepDataAsset> FootstepDataAsset;

public:
	void PlayFootstepSound() const;

	void PlayJumpSound() const;

	void PlayLandSound() const;

	void PlayFootstepCameraShake() const;

	void PlayJumpCameraShake() const;

	void PlayLandCameraShake() const;

private:
	FVector GetFootstepSoundPlayLocation() const;
	
private:
	FFootstepSound TraceFootsteps() const;

	UFUNCTION()
	void OnFootstepTimelineUpdate(const float InTime);

	UFUNCTION()
	void OnFootstepTimelineFinish();

	UFUNCTION()
	void OnJump();

	UFUNCTION()
	void OnLand(const FHitResult& Hit);
	
};
