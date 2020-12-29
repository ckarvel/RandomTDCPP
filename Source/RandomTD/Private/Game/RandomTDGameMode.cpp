// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/RandomTDGameMode.h"
#include "Controllers/RandomTDPlayerController.h"
#include "RandomTD/RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
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
	StockManager = GetWorld()->SpawnActor<AStockManager>(AStockManager::StaticClass());
	EnemyFactory = GetWorld()->SpawnActor<ARandomTDEnemyFactory>(EnemyFactoryClass);
	GridFactory = GetWorld()->SpawnActor<ARandomTDGridFactory>(GridFactoryClass);
	TowerFactory = GetWorld()->SpawnActor<ARandomTDTowerFactory>(TowerFactoryClass);

#if WITH_EDITOR
	StockManager->SetFolderPath("Manager");
	EnemyFactory->SetFolderPath("Factory");
	GridFactory->SetFolderPath("Factory");
	TowerFactory->SetFolderPath("Factory");
#endif

	Super::StartPlay(); // spawns player controller and the rest
}
