// Copyright Lede Studios. All Rights Reserved.


#include "FootstepComponent.h"

#include "Components/CapsuleComponent.h"
#include "Data/FootstepDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/GameplayPlayerCharacter.h"
#include "Player/GameplayPlayerController.h"
#include "Sound/SoundCue.h"

UFootstepComponent::UFootstepComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFootstepComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = CastChecked<AGameplayPlayerCharacter>(GetOwner());
	OwnerController = CastChecked<AGameplayPlayerController>(Owner->GetController());

	Owner->OnJump.AddDynamic(this, &UFootstepComponent::OnJump);
	Owner->OnLand.AddDynamic(this, &UFootstepComponent::OnLand);
	
	FOnTimelineFloat OnUpdate;
	OnUpdate.BindDynamic(this, &UFootstepComponent::OnFootstepTimelineUpdate);
	FootstepTimeline.AddInterpFloat(CurveFloat, OnUpdate);
	
	FOnTimelineEvent OnFinish;
	OnFinish.BindDynamic(this, &UFootstepComponent::OnFootstepTimelineFinish);
	FootstepTimeline.SetTimelineFinishedFunc(OnFinish);
	
	FootstepTimeline.SetLooping(false);
	FootstepTimeline.SetPlayRate(MovementSpeed);
}

void UFootstepComponent::TickComponent(const float DeltaTime, const ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FootstepTimeline.TickTimeline(DeltaTime);
	
	if (Owner.IsValid())
	{
		// 플레이어가 지면 위에 있을 때
		if (!Owner->GetCharacterMovement()->IsFalling())
		{
			// 플레이어가 이동 중일 때
			if (Owner->GetVelocity().Length() > 0)
			{
				// 이동 발자국 사운드 재생
				FootstepTimeline.Play();
				return;
			}
		}
	}

	// 이동 발자국 사운드 종료
	FootstepTimeline.Stop();
	FootstepTimeline.SetNewTime(0.f);
}

void UFootstepComponent::SetMovementSpeed(const float InSpeed)
{
	this->MovementSpeed = InSpeed;
	FootstepTimeline.SetPlayRate(MovementSpeed);
}

float UFootstepComponent::GetMovementSpeed() const
{
	return MovementSpeed;
}

FFootstepSound UFootstepComponent::TraceFootsteps() const
{
	if (ensureMsgf(FootstepDataAsset != nullptr, TEXT("FootstepDataAsset is nullptr.")))
	{
		const FVector Origin = Owner->GetActorLocation();
		const FVector Start = FVector(Origin.X, Origin.Y, Origin.Z + 50);
		const FVector End = FVector(Origin.X, Origin.Y, Origin.Z - 150);
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(Owner.Get());
		Params.bReturnPhysicalMaterial = true;
		
		FHitResult Result;
		GetWorld()->LineTraceSingleByChannel(Result, Start, End, ECC_WorldStatic, Params);
		
		if (Result.PhysMaterial.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Footstep Trace Succefully"));
			return FootstepDataAsset->GetFootstepSoundByType(Result.PhysMaterial.Get());
		}

		UE_LOG(LogTemp, Warning, TEXT("Footstep Trace Failed"));
	}
	
	return FFootstepSound();
}

void UFootstepComponent::PlayFootstepSound() const
{
	const FFootstepSound Sound = TraceFootsteps();
	if (Sound.WalkSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this, Sound.WalkSound.Get(), GetFootstepSoundPlayLocation());
	}
}

void UFootstepComponent::PlayJumpSound() const
{
	const FFootstepSound Sound = TraceFootsteps();
	if (Sound.JumpSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this, Sound.JumpSound.Get(), GetFootstepSoundPlayLocation());
	}
}

void UFootstepComponent::PlayLandSound() const
{
	const FFootstepSound Sound = TraceFootsteps();
	if (Sound.LandSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this, Sound.LandSound.Get(), GetFootstepSoundPlayLocation());
	}
}

void UFootstepComponent::PlayFootstepCameraShake() const
{
	if (FootstepDataAsset)
	{
		const FFootstepCameraShake Shake = FootstepDataAsset->FootstepCameraShake;
		if (Shake.WalkCameraShake)
		{
			OwnerController->PlayerCameraManager->StartCameraShake(Shake.WalkCameraShake);
		}
	}
}

void UFootstepComponent::PlayJumpCameraShake() const
{
	if (FootstepDataAsset)
	{
		const FFootstepCameraShake Shake = FootstepDataAsset->FootstepCameraShake;
		if (Shake.JumpCameraShake)
		{
			OwnerController->PlayerCameraManager->StartCameraShake(Shake.JumpCameraShake);
		}
	}
}

void UFootstepComponent::PlayLandCameraShake() const
{
	if (FootstepDataAsset)
	{
		const FFootstepCameraShake Shake = FootstepDataAsset->FootstepCameraShake;
		if (Shake.LandCameraShake)
		{
			OwnerController->PlayerCameraManager->StartCameraShake(Shake.LandCameraShake);
		}
	}
}

FVector UFootstepComponent::GetFootstepSoundPlayLocation() const
{
	const FVector Loc = Owner->GetActorLocation();
	return FVector(Loc.X, Loc.Y, Loc.Z - Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
}

void UFootstepComponent::OnFootstepTimelineUpdate(const float InTime)
{

}

void UFootstepComponent::OnFootstepTimelineFinish()
{
	FootstepTimeline.SetNewTime(0);
	PlayFootstepSound();
	PlayFootstepCameraShake();
}

void UFootstepComponent::OnJump()
{
	PlayJumpSound();
	PlayJumpCameraShake();
}

void UFootstepComponent::OnLand(const FHitResult& Hit)
{
	PlayLandSound();
	PlayLandCameraShake();
}




