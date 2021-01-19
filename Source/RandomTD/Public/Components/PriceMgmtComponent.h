// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/ItemMgmtComponent.h"
#include "PriceMgmtComponent.generated.h"

/////////////////////////////////////////////////////////////////////////////////////
UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RANDOMTD_API UPriceMgmtComponent : public UActorComponent
{
  GENERATED_UCLASS_BODY()

protected:
  /////////////////////////////////////////////////////////////////////////////////////
  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
  /////////////////////////////////////////////////////////////////////////////////////
  virtual void BeginPlay() override;

  /////////////////////////////////////////////////////////////////////////////////////
  UFUNCTION(BlueprintCallable)
  void GeneratePrices();

  UPROPERTY(BlueprintReadWrite)
  TMap<EItemType, float> PriceMap;
  UPROPERTY(BlueprintReadWrite)
  int MinPrice;
  UPROPERTY(BlueprintReadWrite)
  int MaxPrice;
};
