// Fill out your copyright notice in the Description page of Project Settings.

#include "Managers/StockManager.h"
#include "Game/RandomTDGameInstance.h"
#include "FunctionLibrary/GameStateLibrary.h"
#include "Kismet/KismetMathLibrary.h"

///////////////////////////////////////////////////////////////////////////////////////
UStockManager::UStockManager(const FObjectInitializer& ObjectInitializer)
	  : Super(ObjectInitializer)
		, MinPrice(50)
	  , MaxPrice(100)
{
}

///////////////////////////////////////////////////////////////////////////////////////
void UStockManager::SetGameInstance(URandomTDGameInstance* _GI)
{
	GI = _GI;
	UGameStateLibrary::BindToLevelStart(GI, this, &UStockManager::GenerateStockPrices);
}

/////////////////////////////////////////////////////////////////////////////////////
void UStockManager::GenerateStockPrices(int Level)
{
	for (int i = 0; i < StockPrices.Num(); i++)
	{
		int Price = UKismetMathLibrary::RandomIntegerInRange(MinPrice, MaxPrice);
		StockPrices[i] = Price;
	}
	
	PriceChangeEvent.Broadcast(StockPrices);
}
