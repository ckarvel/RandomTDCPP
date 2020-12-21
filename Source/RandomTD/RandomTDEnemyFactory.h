// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomTDEnemyFactory.generated.h"

/////////////////////////////////////////////////////////////////////////////////////
/// @class ARandomTDEnemyFactory
/// @brief Manages lifecycle of @c ARandomTDEnemyCharacter actors.
/// @details Contains a master list of all spawned Enemies which is updated when they
/// are despawned.
UCLASS()
class RANDOMTD_API ARandomTDEnemyFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	/////////////////////////////////////////////////////////////////////////////////////
	ARandomTDEnemyFactory();

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Bind functions to delegates.
	/// @remark @ref StartSpawnTimer() is bound to @ref ARandomTDGameMode::LevelStartEvent.
	/// @remark @ref OnEnemyStateChange() is bound to @ref ARandomTDEnemyCharacter::OnStateChangeEvent.
	virtual void BeginPlay() override;

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Gives reference to newly spawned Enemy actor.
	/// @remark Called from Blueprint when a new Enemy has spawned.
	UFUNCTION(BlueprintCallable, Category = "EnemyBase")
	void AddNewEnemyToList(ARandomTDEnemyCharacter* BP_Enemy);

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief At the start of every round, this timer will indefinitely call
	/// @ref SpawnNewEnemy() once per second.
	/// @remark Is bound to @ref ARandomTDGameMode::LevelStartEvent.
	/// @remark Only cleared by @c SpawnNewEnemy().
	/// @remark Clears @ref EnemiesSpawned counter.
	void StartSpawnTimer(int CurrentLevel);

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Calls @ref SpawnEnemy() and clears @ref SpawnEnemyTimerHandle.
	/// @details Keeps track of how many Enemies are spawned each round. Once that number
	/// reaches [@ref MaxEnemiesPerLevel], the @c SpawnEnemyTimerHandle is cleared.
	/// @see StartSpawnTimer()
	void SpawnNewEnemy();

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Spawns Enemy actor at @c Location.
	/// @remark This is a Blueprint implementable function (event).
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "EnemyBase")
	ARandomTDEnemyCharacter* SpawnEnemy(FVector Location);

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Unselect enemy if any selected
	/// @todo Unselect()
	void Unselect() {};

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Select enemy
	/// @todo Select()
	void Select(ARandomTDEnemyCharacter* Enemy) {};

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Destroys an Enemy actor.
	/// @remark Only called from @ref OnEnemyStateChange().
	UFUNCTION()
	void OnEnemyDestroyed(AActor* Enemy);

	int EnemiesSpawned; ///< Counter used to track number of spawned Enemy actors at the start
											///< of each round.

	FVector SpawnLocation; ///< Location to spawn Enemy actors. This value is the starting
												 ///< point of the Spline Path

	FTimerHandle SpawnEnemyTimerHandle; ///< Timer handle used to spawn Enemy actors.

	TArray<ARandomTDEnemyCharacter*> ListOfEnemies; ///< List of enemy actors in the world.

public:	
	virtual void Tick(float DeltaTime) override;

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Destroys Enemy if Enemy State == Dead or EnemyState == Finished Spline Path
	/// @details This sets a timer to Destroy the Enemy actor in the next tick.
	/// @remark Not sure if next tick is necessary...
	//void OnEnemyStateChange(ARandomTDEnemyCharacter* Enemy);

	UPROPERTY(EditAnywhere, Category = "EnemyBase")
	int MaxEnemiesPerLevel; ///< The number of Enemies to spawn each round.
};
