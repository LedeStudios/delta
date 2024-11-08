// Copyright Lede Studios. All Rights Reserved.


#include "GameplayPlayerCharacter.h"

#include "Camera/CameraComponent.h"

AGameplayPlayerCharacter::AGameplayPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(GetRootComponent());
}

void AGameplayPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

