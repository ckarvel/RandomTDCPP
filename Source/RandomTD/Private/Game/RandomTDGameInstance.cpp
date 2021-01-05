// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RandomTDGameInstance.h"
#include "Managers/LevelManager.h"
#include "Managers/StockManager.h"

/////////////////////////////////////////////////////////////////////////////////////
void URandomTDGameInstance::Init()
{
  Super::Init();

  LevelManager = NewObject<ULevelManager>(ULevelManager::StaticClass());
  StockManager = NewObject<UStockManager>(UStockManager::StaticClass());
}

/////////////////////////////////////////////////////////////////////////////////////
void URandomTDGameInstance::OnStart()
{
  Super::OnStart();
  LevelManager->SetTimerManager(&GetTimerManager());
  LevelManager->StartTimers();
  StockManager->SetGameInstance(this);
}
