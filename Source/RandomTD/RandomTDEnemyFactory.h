// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomTDEnemyCharacter.h"
#include "RandomTDEnemyFactory.generated.h"

UCLASS()
class RANDOMTD_API ARandomTDEnemyFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	ARandomTDEnemyFactory();

private:
	int EnemiesSpawned; // num enemies spawned in 1 round

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void BeginPlay() override;
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Called by BP_TowerFactory so it can provide us with a reference
	/// to the newly spawned tower.
	UFUNCTION(BlueprintCallable, Category = "EnemyBase")
	void AddNewEnemyToList(ARandomTDEnemyCharacter* Enemy);
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	void StartSpawnTimer(int CurrentRound);
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Calls SpawnEnemy in BP.
	/// Handles clearing timer when called [@a kMaxEnemiesPerRound] number of times
	/// Only want BP to spawn enemy.
	void SpawnNewEnemy();
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "EnemyBase")
	void SpawnEnemy();
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Unselect enemy if any selected
	/// @todo
	void Unselect() {};
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Selects an Enemy to see info
	/// @todo
	void Select(ARandomTDEnemyCharacter* Enemy) {};
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Destroys a tower.
	/// @remark This function is bound to the TowerBase's delegate function. That means
	/// this function is called when TowerBase calls its delegate. This is not directly called.
	/// @param Tower Tower to be deleted.
	/// @todo This function also deletes the tower/grid key/value from the map and it sets the grid
	/// to valid... idk if this is the right place for that but it will do for now.
	void DestroyEnemy(ARandomTDEnemyCharacter* Enemy);

	FTimerHandle SpawnEnemyTimerHandle;
	TArray<ARandomTDEnemyCharacter*> ListOfEnemies; ///< List of enemy actors in the world.

public:	
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "EnemyBase")
	int MaxEnemiesPerRound;
};
