// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Managers/LevelManager.h"
#include "Managers/StockManager.h"
#include "Factories/EnemyFactory.h"
#include "Factories/GridFactory.h"
#include "Factories/TowerFactory.h"
#include "GameFramework/GameModeBase.h"
#include "RandomTDGameMode.generated.h"

///////////////////////////////////////////////////////////////////////////
/// @class GameMode 
/// @brief Handles game rules.
UCLASS(minimalapi)
class ARandomTDGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/////////////////////////////////////////////////////////////////////////////////////
	ARandomTDGameMode();

	/////////////////////////////////////////////////////////////////////////////////////
	virtual void StartPlay() override;

	/////////////////////////////////////////////////////////////////////////////////////
	static ARandomTDEnemyFactory* GetEnemyFactory() { return EnemyFactory; }

	/////////////////////////////////////////////////////////////////////////////////////
	static ARandomTDGridFactory* GetGridFactory() { return GridFactory; }

	/////////////////////////////////////////////////////////////////////////////////////
	static ARandomTDTowerFactory* GetTowerFactory() { return TowerFactory; }

protected:
	UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = Factories)
	TSubclassOf<ARandomTDEnemyFactory> EnemyFactoryClass;

	UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = Factories)
	TSubclassOf<ARandomTDGridFactory> GridFactoryClass;	

	UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = Factories)
	TSubclassOf<ARandomTDTowerFactory> TowerFactoryClass;

	static ARandomTDEnemyFactory* EnemyFactory;

	static ARandomTDGridFactory* GridFactory;

	static ARandomTDTowerFactory* TowerFactory;
};
