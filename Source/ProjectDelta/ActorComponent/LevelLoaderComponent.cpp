// Copyright Lede Studios. All Rights Reserved.


#include "LevelLoaderComponent.h"

#include "Kismet/GameplayStatics.h"

ULevelLoaderComponent::ULevelLoaderComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULevelLoaderComponent::LoadDefault()
{
	if (Rooms.IsEmpty() || LivingRooms.IsEmpty() || Hallways.IsEmpty() || Stairways.IsEmpty() || Holes.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot load default levels."));
		return;
	}
	
	Load(Rooms[0], LivingRooms[0], Hallways[0], Stairways[0], Holes[0]);
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

void ULevelLoaderComponent::LoadLevels(TArray<TSoftObjectPtr<UWorld>> InLevels)
{
	for (const TSoftObjectPtr<UWorld> InLevel : InLevels)
	{
		LoadedLevel.Add(InLevel);
		UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, InLevel, true, false, FLatentActionInfo());
	}
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

