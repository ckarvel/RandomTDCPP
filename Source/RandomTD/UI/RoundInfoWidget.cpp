// Fill out your copyright notice in the Description page of Project Settings.


#include "RoundInfoWidget.h"
#include "RandomTD/RandomTDGameMode.h"
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
	kSecondsPerLevel = ARandomTDGameMode::GetLevelManager()->GetSecondsPerLevel();
	kPreLevelSeconds = ARandomTDGameMode::GetLevelManager()->GetPreLevelSeconds();

	// this may cause a crash in unreal. this should be set in BeginPlay or something
	// it hasn't crashed here yet tho... so ill just hold off.
	ARandomTDGameMode::GetLevelManager()->LevelStartEvent.AddUObject(this, &URoundInfoWidget::SetCurrentLevel);
	ARandomTDGameMode::GetLevelManager()->LevelSecondElapsedEvent.AddUObject(this, &URoundInfoWidget::SetLevelTime);
	ARandomTDGameMode::GetStockManager()->PriceChangeEvent.AddUObject(this, &URoundInfoWidget::SetStockPrices);
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
