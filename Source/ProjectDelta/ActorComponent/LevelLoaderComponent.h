// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelLoaderComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTDELTA_API ULevelLoaderComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULevelLoaderComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="LevelLoader")
	TArray<TSoftObjectPtr<UWorld>> Defaults;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="LevelLoader")
	TArray<TSoftObjectPtr<UWorld>> Rooms;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="LevelLoader")
	TArray<TSoftObjectPtr<UWorld>> LivingRooms;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="LevelLoader")
	TArray<TSoftObjectPtr<UWorld>> Hallways;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="LevelLoader")
	TArray<TSoftObjectPtr<UWorld>> Stairways;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="LevelLoader")
	TArray<TSoftObjectPtr<UWorld>> Holes;

private:
	UPROPERTY()
	TArray<TSoftObjectPtr<UWorld>> LoadedLevel;
	
public:
	UFUNCTION(BlueprintCallable, Category="LevelLoader")
	void LoadDefault();

	UFUNCTION(BlueprintCallable, Category="LevelLoader")
	void LoadRandom();

	UFUNCTION(BlueprintCallable, Category="LevelLoader")
	void Load(TSoftObjectPtr<UWorld> InRoom, TSoftObjectPtr<UWorld> InLivingRoom, TSoftObjectPtr<UWorld> InHallway, TSoftObjectPtr<UWorld> InStairway, TSoftObjectPtr<UWorld> InHole);
	
	UFUNCTION(BlueprintCallable, Category="LevelLoader")
	void Unload();

private:
	UPROPERTY()
	TArray<TSoftObjectPtr<UWorld>> LevelsToLoad;

	int32 CurrentLoadIndex = 0;
	
private:
	void LoadLevels(const TArray<TSoftObjectPtr<UWorld>>& InLevels);

	void LoadNextLevel(int32 InIndex);

	UFUNCTION()
	void OnLoaded();
	
};
