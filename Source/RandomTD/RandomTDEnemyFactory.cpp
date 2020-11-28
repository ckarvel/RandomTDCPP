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
	, SpawnLocation(FVector())
	, MaxEnemiesPerRound(10)
{
	PrimaryActorTick.bCanEverTick = false; // no ticking
//#ifdef UE_BUILD_DEBUG
//	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDEnemyFactory::Constructor"));
//#endif
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyFactory::BeginPlay()
{
	Super::BeginPlay();
//#ifdef UE_BUILD_DEBUG
//	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDEnemyFactory::BeginPlay"));
//#endif

	// spawn enemy delegate
	ARandomTDGameMode::RoundStartEvent.AddUObject(this, &ARandomTDEnemyFactory::StartSpawnTimer);

	// [state change == finished path] or [state change == dead] delegate
	ARandomTDEnemyCharacter::OnStateChangeEvent.AddUObject(this, &ARandomTDEnemyFactory::OnEnemyStateChange);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/////////////////////////////////////////////////////////////////////////////////////
// Call from GameMode
void ARandomTDEnemyFactory::StartSpawnTimer(int CurrentRound)
{
//#ifdef UE_BUILD_DEBUG
//	UE_LOG(LogRandomTD, Log, TEXT("StartSpawnTimer:Round %d"), CurrentRound);
//#endif
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
//#ifdef UE_BUILD_DEBUG
//		UE_LOG(LogRandomTD, Log, TEXT("ARandomTDEnemyFactory::EnemiesSpawned"));
//#endif
		// we're done spawning enemies for this round
		GetWorldTimerManager().ClearTimer(SpawnEnemyTimerHandle);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// Called from EnemyCharacter
void ARandomTDEnemyFactory::OnEnemyStateChange(ARandomTDEnemyCharacter* Enemy)
{
	// if state == dead or finished path
	FTimerDelegate DespawnDelegate = FTimerDelegate::CreateUObject(this, &ARandomTDEnemyFactory::DestroyEnemy, Enemy);
	// destroy enemy in the next tick
	// I'm not sure if this is necessary... I added this so Behavior Tree has a chance to
	// stop before deletion.
	GetWorldTimerManager().SetTimerForNextTick(DespawnDelegate);
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDEnemyFactory::OnEnemyStateChange"));
#endif
}

/////////////////////////////////////////////////////////////////////////////////////
// Called from EnemyCharacter
void ARandomTDEnemyFactory::DestroyEnemy(ARandomTDEnemyCharacter* Enemy)
{
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDEnemyFactory::DestroyEnemy"));
#endif	
	ListOfEnemies.Remove(Enemy);
	Enemy->Destroy();
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
// Called from Blueprint Derived class
void ARandomTDEnemyFactory::AddNewEnemyToList(ARandomTDEnemyCharacter* Enemy)
{
#if WITH_EDITOR
	Enemy->SetFolderPath("Enemy");
#endif
	ListOfEnemies.Add(Enemy);
}
