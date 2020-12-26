// Fill out your copyright notice in the Description page of Project Settings.

#include "Managers/StockManager.h"
#include "Game/RandomTDGameMode.h"
#include "Kismet/KismetMathLibrary.h"
#include "RandomTD/RandomTD.h"

///////////////////////////////////////////////////////////////////////////////////////
AStockManager::AStockManager()
	: MinPrice(50)
	, MaxPrice(100)
{
	PrimaryActorTick.bCanEverTick = false; // no ticking
	StockPrices.AddZeroed(3);
}

/////////////////////////////////////////////////////////////////////////////////////
void AStockManager::BeginPlay()
{
	Super::BeginPlay();

	ARandomTDGameMode::GetLevelManager()->LevelStartEvent.AddUObject(this, &AStockManager::GenerateStockPrices);
}

/////////////////////////////////////////////////////////////////////////////////////
void AStockManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/////////////////////////////////////////////////////////////////////////////////////
void AStockManager::GenerateStockPrices(int Level)
{
	for (int i = 0; i < StockPrices.Num(); i++)
	{
		int Price = UKismetMathLibrary::RandomIntegerInRange(MinPrice, MaxPrice);
		StockPrices[i] = Price;
	}
	
	PriceChangeEvent.Broadcast(StockPrices);
}
