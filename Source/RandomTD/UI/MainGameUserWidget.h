// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Internationalization/Internationalization.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "MainGameUserWidget.generated.h"

/////////////////////////////////////////////////////////////////////////////////////
/// @remark Delegate binding happens in constructor. This can cause a crash if UI is
/// constructed before dependencies.
UCLASS()
class RANDOMTD_API UMainGameUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	UMainGameUserWidget(const FObjectInitializer& ObjectInitializer);

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	void SetCurrentRound(int Value) { CurrentRound = Value; }

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	void SetRoundTime(int Value) { RoundElapsedTime = Value; }

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	/// UI Text Bind functions
	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Game")
	FText GetRoundCount() const
	{
		return  FText::FromString(FString::FromInt(CurrentRound));
	}

	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Game")
	FText GetElapsedSeconds() const
	{
		return FText::FromString(FString::FromInt(RoundElapsedTime));
	}

	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Game")
	FText GetSecondsPerRound() const
	{
		int Seconds = CurrentRound ? kSecondsPerRound : kPreRoundSeconds;
		return FText::FromString(FString::FromInt(Seconds));
	}

	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Game")
	float GetElapsedPercentage() const
	{
		// number to be divided
		int TotalSeconds = CurrentRound ? kSecondsPerRound : kPreRoundSeconds;
		if (!TotalSeconds)
			return 0.0; // just in case...

		float Percent = (float) RoundElapsedTime / (float) TotalSeconds;
		return Percent;
	}

	int CurrentRound;

	int RoundElapsedTime;

	int kSecondsPerRound;

	int kPreRoundSeconds;
};
