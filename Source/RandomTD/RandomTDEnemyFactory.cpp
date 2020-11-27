// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomTDEnemyFactory.h"
#include "RandomTDEnemyController.h"
#include "RandomTDEnemyCharacter.h"
#include "RandomTDPathSpline.h"
#include "RandomTDGameMode.h"
#include "RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDEnemyFactory::ARandomTDEnemyFactory()
	: EnemiesSpawned(0)
	, MaxEnemiesPerRound(10)
	, SpawnLocation(FVector())
{
	PrimaryActorTick.bCanEverTick = false; // no ticking
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDTowerFactory::Constructor"));
#endif
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyFactory::BeginPlay()
{
	Super::BeginPlay();
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDEnemyFactory::BeginPlay"));
#endif

	ARandomTDGameMode::RoundStartEvent.AddUObject(this, &ARandomTDEnemyFactory::StartSpawnTimer);
	ARandomTDEnemyController::DestroyEnemyEvent.BindUObject(this, &ARandomTDEnemyFactory::DestroyEnemy);
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyFactory::StartSpawnTimer(int CurrentRound)
{
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("StartSpawnTimer:Round %d"), CurrentRound);
#endif
	// reset enemy counter
	EnemiesSpawned = 0;
	GetWorldTimerManager().SetTimer(SpawnEnemyTimerHandle,
		this,
		&ARandomTDEnemyFactory::SpawnNewEnemy,
		1.0f,
		true,
		0.0f);
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyFactory::SpawnNewEnemy()
{
	// call BP to spawn specific enemy asset
	SpawnEnemy(ARandomTDPathSpline::GetWaypointAtIndex(0)); // get first location
	EnemiesSpawned++;

	if (EnemiesSpawned == MaxEnemiesPerRound)
	{
#ifdef UE_BUILD_DEBUG
		UE_LOG(LogRandomTD, Log, TEXT("ARandomTDEnemyFactory::EnemiesSpawned"));
#endif
		// we're done spawning enemies for this round
		GetWorldTimerManager().ClearTimer(SpawnEnemyTimerHandle);
	}
}
/////////////////////////////////////////////////////////////////////////////////////
//void ARandomTDEnemyFactory::UnselectAll()
//{
//	for (auto& pair : ListOfActiveTowerRefs)
//	{
//		pair.Key->Unselect();
//	}
//}
//void ARandomTDEnemyFactory::Select(ARandomTDTowerBase* Tower)
//{
//	Tower->Select();
//}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyFactory::DestroyEnemy(ARandomTDEnemyCharacter* Enemy)
{
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDEnemyFactory::DestroyEnemy"));
#endif	
	ListOfEnemies.Remove(Enemy);
	Enemy->Destroy();
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyFactory::AddNewEnemyToList(ARandomTDEnemyCharacter* Enemy)
{
	ListOfEnemies.Add(Enemy);
}
/////////////////////////////////////////////////////////////////////////////////////