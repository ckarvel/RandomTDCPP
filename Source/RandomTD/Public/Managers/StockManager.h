// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StockManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStockPriceChange, TArray<int>);

class URandomTDGameInstance;

/////////////////////////////////////////////////////////////////////////////////////
UCLASS()
class RANDOMTD_API UStockManager : public UObject
{
  GENERATED_UCLASS_BODY()

private:
  /////////////////////////////////////////////////////////////////////////////////////
  void SetGameInstance(URandomTDGameInstance* GI);

  URandomTDGameInstance* GI;
  int MinPrice; ///< Minimum price to sell stock
  int MaxPrice; ///< Maximum price to sell stock
  TArray<int> StockPrices;

  friend class URandomTDGameInstance;

public:
  /////////////////////////////////////////////////////////////////////////////////////
  UStockManager();

  /////////////////////////////////////////////////////////////////////////////////////
  void GenerateStockPrices(int Level);

  FOnStockPriceChange PriceChangeEvent;
};
