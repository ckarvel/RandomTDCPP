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
  URoundInfoWidget(const FObjectInitializer& ObjectInitializer);

	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Game")
	void Init();

	/////////////////////////////////////////////////////////////////////////////////////
	void SetStockPrices(TArray<int> Prices);

	/////////////////////////////////////////////////////////////////////////////////////
	void SetCurrentLevel(int Value) { CurrentLevel = Value; }

	/////////////////////////////////////////////////////////////////////////////////////
	void SetLevelTime(int Value) { LevelElapsedTime = Value; }

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
	float GetElapsedPercentage() const;

	/////////////////////////////////////////////////////////////////////////////////////
  UFUNCTION(BlueprintCallable, Category = "Game")
  FText GetStockPriceA() const
  {
    //return FText::FromString(FString::FromInt(StockPrices[0]));
		return FText::FromString("hello");
  }

	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Game")
  FText GetStockPriceB() const
  {
    //return FText::FromString(FString::FromInt(StockPrices[1]));
		return FText::FromString("hello");
  }

	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Game")
  FText GetStockPriceC() const
  {
    //return FText::FromString(FString::FromInt(StockPrices[2]));
		return FText::FromString("hello");
  }

protected:
  int CurrentLevel;

  int LevelElapsedTime;

  int kSecondsPerLevel;

  int kPreLevelSeconds;

	TArray<int> StockPrices;
};
