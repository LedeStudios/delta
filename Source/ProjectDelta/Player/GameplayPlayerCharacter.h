// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayPlayerCharacter.generated.h"

class UFootstepComponent;
class UCameraComponent;
class USpringArmComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJump_Delegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLand_Delegate, const FHitResult&, Hit);

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

	// ====================================================================================
	//  Footstep
	// ====================================================================================
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Footstep")
	TObjectPtr<UFootstepComponent> FootstepComponent;

public:
	UFootstepComponent* GetFootstepComponent() { return FootstepComponent; }

// ====================================================================================
//  Jump & Land Callbacks
// ====================================================================================
public:
	FOnJump_Delegate OnJump;
	FOnLand_Delegate OnLand;

private:
	virtual void OnJumped_Implementation() override;
	virtual void Landed(const FHitResult& Hit) override;
	
};
