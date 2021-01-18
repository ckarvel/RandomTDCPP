// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PriceMgmtComponent.h"
#include "Game/RandomTDGameInstance.h"
#include "Components/LevelMgmtComponent.h"
#include "Kismet/KismetMathLibrary.h"

///////////////////////////////////////////////////////////////////////////////////////
UPriceMgmtComponent::UPriceMgmtComponent()
  : MinPrice(50)
  , MaxPrice(100)
{
	PrimaryComponentTick.bCanEverTick = false;
}

///////////////////////////////////////////////////////////////////////////////////////
void UPriceMgmtComponent::BeginPlay()
{
	Super::BeginPlay();
}

///////////////////////////////////////////////////////////////////////////////////////
void UPriceMgmtComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

/////////////////////////////////////////////////////////////////////////////////////
void UPriceMgmtComponent::GenerateStockPrices(int Level)
{
  for (int i = 0; i < StockPrices.Num(); i++)
  {
    int Price = UKismetMathLibrary::RandomIntegerInRange(MinPrice, MaxPrice);
    StockPrices[i] = Price;
  }

  PriceChangeEvent.Broadcast(StockPrices);
}
