// Fill out your copyright notice in the Description page of Project Settings.

#include "Factories/EnemyFactory.h"
#include "FunctionLibrary/GameStateLibrary.h"
#include "Controllers/EnemyController.h"
#include "Characters/EnemyCharacter.h"
#include "WorldActors/PathSpline.h"
#include "Game/RandomTDGameMode.h"
#include "RandomTD/RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDEnemyFactory::ARandomTDEnemyFactory()
	: EnemiesSpawned(0)
	, SpawnLocation(FVector())
	, MaxEnemiesPerLevel(10)
{
	PrimaryActorTick.bCanEverTick = false; // no ticking
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyFactory::BeginPlay()
{
	Super::BeginPlay();

	// spawn enemy delegate
	auto* GI = GetGameInstance();
	UGameStateLibrary::BindToLevelStart(GI, this, &ARandomTDEnemyFactory::StartSpawnTimer);

	// [state change == finished path] or [state change == dead] delegate
	//ARandomTDEnemyCharacter::OnStateChangeEvent.AddUObject(this, &ARandomTDEnemyFactory::OnEnemyStateChange);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyFactory::StartSpawnTimer(int CurrentLevel)
{
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
	ARandomTDEnemyCharacter* Enemy = SpawnEnemy(ARandomTDPathSpline::GetWaypointAtIndex(0)); // get first location
	EnemiesSpawned++;

	if (EnemiesSpawned == MaxEnemiesPerLevel)
	{
		// we're done spawning enemies for this round
		GetWorldTimerManager().ClearTimer(SpawnEnemyTimerHandle);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//void ARandomTDEnemyFactory::OnEnemyStateChange(ARandomTDEnemyCharacter* Enemy)
//{
//	// if state == dead or finished path
//	FTimerDelegate DespawnDelegate = FTimerDelegate::CreateUObject(this, &ARandomTDEnemyFactory::DestroyEnemy, Enemy);
//	// destroy enemy in the next tick
//	// I'm not sure if this is necessary... I added this so Behavior Tree has a chance to
//	// stop before deletion.
//	GetWorldTimerManager().SetTimerForNextTick(DespawnDelegate);
//#ifdef UE_BUILD_DEBUG
//	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDEnemyFactory::OnEnemyStateChange"));
//#endif
//}

/////////////////////////////////////////////////////////////////////////////////////
//void ARandomTDEnemyFactory::UnselectAll()
//{
//	for (auto& pair : ListOfActiveTowerRefs)
//	{
//		pair.Key->Unselect();
//	}
//}
//void ARandomTDEnemyFactory::Select(ARandomTDTowerCharacter* Tower)
//{
//	Tower->Select();
//}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyFactory::AddNewEnemyToList(ARandomTDEnemyCharacter* BP_Enemy)
{
#if WITH_EDITOR
	BP_Enemy->SetFolderPath("Enemy");
	BP_Enemy->GetController()->SetFolderPath("Controller");
#endif
	ListOfEnemies.Add(BP_Enemy);

	// notify us when tower is removed
	BP_Enemy->OnDestroyed.AddDynamic(this, &ARandomTDEnemyFactory::OnEnemyDestroyed);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyFactory::OnEnemyDestroyed(AActor* Enemy)
{
	int Index = ListOfEnemies.Find(Cast<ARandomTDEnemyCharacter>(Enemy));
	ListOfEnemies.RemoveAt(Index);
}
