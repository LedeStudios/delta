// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PROJECTDELTA_API AGameplayPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGameplayPlayerCharacter();

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player")
	TObjectPtr<UCameraComponent> CameraComponent;
	
};
