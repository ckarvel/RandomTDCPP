// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/RoundInfoWidget.h"
#include "FunctionLibrary/GameStateLibrary.h"
#include "Game/RandomTDGameMode.h"
#include "RandomTD/RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
URoundInfoWidget::URoundInfoWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, CurrentLevel(0)
	, LevelElapsedTime(0.0)
{
	StockPrices.AddZeroed(3);
}

/////////////////////////////////////////////////////////////////////////////////////
void URoundInfoWidget::Init()
{
	auto* GI = GetGameInstance();
	kSecondsPerLevel = UGameStateLibrary::GetSecondsPerLevel(GI);
	kPreLevelSeconds = UGameStateLibrary::GetPreLevelSeconds(GI);

	UGameStateLibrary::BindToLevelStart(GI, this, &URoundInfoWidget::SetCurrentLevel);
	UGameStateLibrary::BindToSecondElapsed(GI, this, &URoundInfoWidget::SetLevelTime);
	UGameStateLibrary::BindToPriceChange(GI, this, &URoundInfoWidget::SetStockPrices);
}

/////////////////////////////////////////////////////////////////////////////////////
float URoundInfoWidget::GetElapsedPercentage() const
{
  // number to be divided
  int TotalSeconds = CurrentLevel ? kSecondsPerLevel : kPreLevelSeconds;
  if (!TotalSeconds)
    return 0.0; // just in case...

  float Percent = (float)LevelElapsedTime / (float)TotalSeconds;
  return Percent;
}

/////////////////////////////////////////////////////////////////////////////////////
void URoundInfoWidget::SetStockPrices(TArray<int> Prices)
{
	StockPrices = Prices;
}
