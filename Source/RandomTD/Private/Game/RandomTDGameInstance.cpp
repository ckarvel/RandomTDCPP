// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/RandomTDGameInstance.h"
#include "Managers/LevelManager.h"
#include "Managers/PriceManager.h"

/////////////////////////////////////////////////////////////////////////////////////
void URandomTDGameInstance::Init()
{
  Super::Init();

  LevelManager = NewObject<ULevelManager>(ULevelManager::StaticClass());
  PriceManager = NewObject<UPriceManager>(UPriceManager::StaticClass());
}

/////////////////////////////////////////////////////////////////////////////////////
void URandomTDGameInstance::OnStart()
{
  Super::OnStart();
  LevelManager->SetTimerManager(&GetTimerManager());
  LevelManager->StartTimers();
  PriceManager->SetGameInstance(this);
}
