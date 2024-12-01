// Copyright Lede Studios. All Rights Reserved.


#include "LevelLoaderComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

ULevelLoaderComponent::ULevelLoaderComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULevelLoaderComponent::LoadDefault()
{
	LoadLevels(Defaults);
}

void ULevelLoaderComponent::LoadRandom()
{
	if (Rooms.IsEmpty() || LivingRooms.IsEmpty() || Hallways.IsEmpty() || Stairways.IsEmpty() || Holes.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot load random levels."));
		return;
	}

	int32 Index = 0;
	FRandomStream Random;
	Random.GenerateNewSeed();

	Index = Random.RandRange(0, Rooms.Num() - 1);
	TSoftObjectPtr<UWorld> Room = Rooms[Index];

	Index = Random.RandRange(0, LivingRooms.Num() - 1);
	TSoftObjectPtr<UWorld> LivingRoom = LivingRooms[Index];
	
	Index = Random.RandRange(0, Hallways.Num() - 1);
	TSoftObjectPtr<UWorld> Hallway = Hallways[Index];

	Index = Random.RandRange(0, Stairways.Num() - 1);
	TSoftObjectPtr<UWorld> Stairway = Stairways[Index];

	Index = Random.RandRange(0, Holes.Num() - 1);
	TSoftObjectPtr<UWorld> Hole = Holes[Index];

	Load(Room, LivingRoom, Hallway, Stairway, Hole);
}

void ULevelLoaderComponent::Load(TSoftObjectPtr<UWorld> InRoom, TSoftObjectPtr<UWorld> InLivingRoom,
	TSoftObjectPtr<UWorld> InHallway, TSoftObjectPtr<UWorld> InStairway, TSoftObjectPtr<UWorld> InHole)
{
	TArray<TSoftObjectPtr<UWorld>> Levels;
	Levels.Add(InRoom);
	Levels.Add(InLivingRoom);
	Levels.Add(InHallway);
	Levels.Add(InStairway);
	Levels.Add(InHole);
	LoadLevels(Levels);
}

void ULevelLoaderComponent::Unload()
{
	if (!LoadedLevel.IsEmpty())
	{
		for (const auto Level : LoadedLevel)
		{
			const FLatentActionInfo Action;
			UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(this, Level, Action, false);
		}
		LoadedLevel.Reset();
	}
}

void ULevelLoaderComponent::LoadLevels(const TArray<TSoftObjectPtr<UWorld>>& InLevels)
{
	LevelsToLoad = InLevels;
	LoadNextLevel(0);
}

void ULevelLoaderComponent::LoadNextLevel(const int32 InIndex)
{
	if (InIndex >= LevelsToLoad.Num())
	{
		if (ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			TArray<AActor*> PlayerStarts;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

			if (PlayerStarts.Num() > 0)
			{
				Character->SetActorTransform(PlayerStarts[0]->GetActorTransform());
				Character->GetController()->SetControlRotation(Character->GetActorRotation());
			}
		}
		return;
	}

	CurrentLoadIndex = InIndex;
	
	FLatentActionInfo LatentInfo;
	LatentInfo.UUID = 0;
	LatentInfo.Linkage = 0;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("OnLoaded");
	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, LevelsToLoad[InIndex], true, false, LatentInfo);
}

void ULevelLoaderComponent::OnLoaded()
{
	UE_LOG(LogTemp, Warning, TEXT("Level loaded: %s"), *LevelsToLoad[CurrentLoadIndex].GetAssetName());
	LoadNextLevel(++CurrentLoadIndex);
}

