// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayPlayerController.generated.h"

class AGameplayPlayerCharacter;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteract);

UCLASS()
class PROJECTDELTA_API AGameplayPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGameplayPlayerController();

public:
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

protected:
	TWeakObjectPtr<AGameplayPlayerCharacter> PlayerCharacter;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Player")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Player")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Player")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Player")
	TObjectPtr<UInputAction> InteractAction;

protected:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Interact();

public:
	UPROPERTY(BlueprintAssignable, Category="Player")
	FOnInteract OnInteract;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta=(UIMin=0.f, UIMax=180.f))
	float MaxPitchAngle = 45.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input", meta=(UIMin=-180.f, UIMax=0.f))
	float MinPitchAngle = -45.f;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(UIMin=0.f, UIMax=1.f))
	float MouseX = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(UIMin=0.f, UIMax=1.f))
	float MouseY = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(UIMin=0.f, UIMax=1.f))
	float MusicVolume = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", meta=(UIMin=0.f, UIMax=1.f))
	float EffectVolume = 0.5f;
	
};
