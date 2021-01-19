// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RandomTDGameInstance.h"
#include "Components/ItemMgmtComponent.h"
#include "Components/LevelMgmtComponent.h"
#include "Components/PriceMgmtComponent.h"

/////////////////////////////////////////////////////////////////////////////////////
URandomTDGameInstance::URandomTDGameInstance(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
{
  PriceManagerClass = UPriceMgmtComponent::StaticClass();
}

/////////////////////////////////////////////////////////////////////////////////////
void URandomTDGameInstance::Init()
{
  Super::Init();

  ItemManager = NewObject<UItemMgmtComponent>(UItemMgmtComponent::StaticClass());
  LevelManager = NewObject<ULevelMgmtComponent>(ULevelMgmtComponent::StaticClass());
  PriceManager = NewObject<UPriceMgmtComponent>(this, PriceManagerClass);
}

/////////////////////////////////////////////////////////////////////////////////////
void URandomTDGameInstance::OnStart()
{
  Super::OnStart();

  LevelManager->RegisterComponentWithWorld(GetWorld());
  PriceManager->RegisterComponentWithWorld(GetWorld());
  PriceManager->BeginPlay();
}

/////////////////////////////////////////////////////////////////////////////////////
UItemMgmtComponent* URandomTDGameInstance::GetItemManager()
{
  return ItemManager;
}

/////////////////////////////////////////////////////////////////////////////////////
ULevelMgmtComponent* URandomTDGameInstance::GetLevelManager()
{
  return LevelManager;
}

/////////////////////////////////////////////////////////////////////////////////////
UPriceMgmtComponent* URandomTDGameInstance::GetPriceManager()
{
  return PriceManager;
}