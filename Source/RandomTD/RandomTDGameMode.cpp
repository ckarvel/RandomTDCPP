// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomTDGameMode.h"
#include "RandomTDPlayerController.h"
#include "Managers/LevelManager.h"
#include "RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
ALevelManager* ARandomTDGameMode::LevelManager;

AStockManager* ARandomTDGameMode::StockManager;

ARandomTDEnemyFactory* ARandomTDGameMode::EnemyFactory;

ARandomTDGridFactory* ARandomTDGameMode::GridFactory;

ARandomTDTowerFactory* ARandomTDGameMode::TowerFactory;

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDGameMode::ARandomTDGameMode()
{
	PlayerControllerClass = ARandomTDPlayerController::StaticClass();
	EnemyFactoryClass = ARandomTDEnemyFactory::StaticClass();
	GridFactoryClass = ARandomTDGridFactory::StaticClass();
	TowerFactoryClass = ARandomTDTowerFactory::StaticClass();
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDGameMode::StartPlay()
{
	Super::StartPlay();
	LevelManager = CreateDefaultSubobject<ALevelManager>("LevelManager");
	EnemyFactory = GetWorld()->SpawnActor<ARandomTDEnemyFactory>(EnemyFactoryClass);
	GridFactory = GetWorld()->SpawnActor<ARandomTDGridFactory>(GridFactoryClass);
	TowerFactory = GetWorld()->SpawnActor<ARandomTDTowerFactory>(TowerFactoryClass);
	LevelManager->Begin();
}
