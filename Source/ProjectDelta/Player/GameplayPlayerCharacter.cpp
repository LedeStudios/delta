// Copyright Lede Studios. All Rights Reserved.


#include "GameplayPlayerCharacter.h"

#include "ActorComponent/FootstepComponent.h"
#include "Camera/CameraComponent.h"

AGameplayPlayerCharacter::AGameplayPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(GetRootComponent());
	
	// Footstep
	FootstepComponent = CreateDefaultSubobject<UFootstepComponent>("FootstepComponent");
}

void AGameplayPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGameplayPlayerCharacter::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();
	
	if (OnJump.IsBound())
	{
		OnJump.Broadcast();
	}
}

void AGameplayPlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (OnLand.IsBound())
	{
		OnLand.Broadcast(Hit);
	}
}