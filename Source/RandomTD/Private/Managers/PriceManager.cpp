// Fill out your copyright notice in the Description page of Project Settings.

#include "Managers/PriceManager.h"
#include "Game/RandomTDGameInstance.h"
#include "FunctionLibrary/GameStateLibrary.h"
#include "Kismet/KismetMathLibrary.h"

///////////////////////////////////////////////////////////////////////////////////////
UPriceManager::UPriceManager(const FObjectInitializer& ObjectInitializer)
	  : Super(ObjectInitializer)
		, MinPrice(50)
	  , MaxPrice(100)
{
}

///////////////////////////////////////////////////////////////////////////////////////
void UPriceManager::SetGameInstance(URandomTDGameInstance* _GI)
{
	GI = _GI;
	UGameStateLibrary::BindToLevelStart(GI, this, &UPriceManager::GenerateStockPrices);
}

/////////////////////////////////////////////////////////////////////////////////////
void UPriceManager::GenerateStockPrices(int Level)
{
	for (int i = 0; i < StockPrices.Num(); i++)
	{
		int Price = UKismetMathLibrary::RandomIntegerInRange(MinPrice, MaxPrice);
		StockPrices[i] = Price;
	}
	
	PriceChangeEvent.Broadcast(StockPrices);
}
