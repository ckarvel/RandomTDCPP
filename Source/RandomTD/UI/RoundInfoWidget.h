// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoundInfoWidget.generated.h"

/////////////////////////////////////////////////////////////////////////////////////
/// @remark Delegate binding happens in constructor. This can cause a crash if UI is
/// constructed before dependencies.
UCLASS()
class RANDOMTD_API URoundInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Game")
	void Init();

	/////////////////////////////////////////////////////////////////////////////////////
	URoundInfoWidget(const FObjectInitializer& ObjectInitializer);

	/////////////////////////////////////////////////////////////////////////////////////
	void SetCurrentLevel(int Value) { CurrentLevel = Value; }

	/////////////////////////////////////////////////////////////////////////////////////
	void SetLevelTime(int Value) { LevelElapsedTime = Value; }

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Game")
		FText GetLevelCount() const
	{
		return  FText::FromString(FString::FromInt(CurrentLevel));
	}

	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Game")
		FText GetElapsedSeconds() const
	{
		return FText::FromString(FString::FromInt(LevelElapsedTime));
	}

	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Game")
		FText GetSecondsPerLevel() const
	{
		int Seconds = CurrentLevel ? kSecondsPerLevel : kPreLevelSeconds;
		return FText::FromString(FString::FromInt(Seconds));
	}

	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Game")
		float GetElapsedPercentage() const
	{
		// number to be divided
		int TotalSeconds = CurrentLevel ? kSecondsPerLevel : kPreLevelSeconds;
		if (!TotalSeconds)
			return 0.0; // just in case...

		float Percent = (float)LevelElapsedTime / (float)TotalSeconds;
		return Percent;
	}

	int CurrentLevel;

	int LevelElapsedTime;

	int kSecondsPerLevel;

	int kPreLevelSeconds;
};
