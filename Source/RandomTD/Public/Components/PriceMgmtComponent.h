// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PriceMgmtComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnStockPriceChange, TArray<int>);

class URandomTDGameInstance;

/////////////////////////////////////////////////////////////////////////////////////
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RANDOMTD_API UPriceMgmtComponent : public UActorComponent
{
	GENERATED_BODY()

private:
  /////////////////////////////////////////////////////////////////////////////////////
  void SetGameInstance(URandomTDGameInstance* GI);

  URandomTDGameInstance* GI;
  int MinPrice; ///< Minimum price to sell stock
  int MaxPrice; ///< Maximum price to sell stock
  TArray<int> StockPrices;

  friend class URandomTDGameInstance;

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	virtual void BeginPlay() override;

  /////////////////////////////////////////////////////////////////////////////////////
  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
  /////////////////////////////////////////////////////////////////////////////////////
  UPriceMgmtComponent();

  /////////////////////////////////////////////////////////////////////////////////////
  void GenerateStockPrices(int Level);

  FOnStockPriceChange PriceChangeEvent;
};
