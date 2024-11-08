// Copyright Lede Studios. All Rights Reserved.


#include "GameplayPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayPlayerCharacter.h"

AGameplayPlayerController::AGameplayPlayerController()
{
}

void AGameplayPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGameplayPlayerController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGameplayPlayerController::Look);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AGameplayPlayerController::Interact);
	}
}

void AGameplayPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	PlayerCharacter = CastChecked<AGameplayPlayerCharacter>(GetCharacter());
}

void AGameplayPlayerController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	PlayerCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
	PlayerCharacter->AddMovementInput(RightDirection, MovementVector.X);
}

void AGameplayPlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	// LookAxisVector.X = LookAxisVector.X / 100 * Settings->MouseX;
	// LookAxisVector.Y = LookAxisVector.Y / 100 * Settings->MouseY;
		
	// add yaw input to controller
	PlayerCharacter->AddControllerYawInput(LookAxisVector.X);
		
	// limit pitch angle
	const float CurrentPitch = PlayerCharacter->GetControlRotation().Pitch;
	const float PitchToUpdate = (CurrentPitch > 180 ? CurrentPitch - 360 : CurrentPitch) - LookAxisVector.Y;
	const float Pitch = FMath::Clamp(PitchToUpdate, MinPitchAngle, MaxPitchAngle);

	// set controller pitch
	FRotator Rotator = PlayerCharacter->GetControlRotation();
	Rotator.Pitch = Pitch;
	if (PlayerCharacter->GetController())
	{
		PlayerCharacter->GetController()->SetControlRotation(Rotator);
	}
}

void AGameplayPlayerController::Interact()
{
	if (OnInteract.IsBound())
	{
		OnInteract.Broadcast();
	}
}
