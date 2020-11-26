// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomTDTowerFactory.generated.h"

/// @class ARandomTDTowerFactory 
/// @brief Handles spawning/despawning towers.
/// 
/// Used as an interface for PlayerController to
/// gain access to specific towers.

UCLASS()
class RANDOMTD_API ARandomTDTowerFactory : public AActor
{
	GENERATED_BODY()
public:
	/////////////////////////////////////////////////////////////////////////////////////
	///@brief Sets default values
	ARandomTDTowerFactory();

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @see ARandomTDPlayerController::BeginPlay()
	virtual void BeginPlay() override;
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Called by BP_TowerFactory so it can provide us with a reference
	/// to the newly spawned tower.
	UFUNCTION(BlueprintCallable, Category = "Tower")
	void AddNewTowerToList(ARandomTDGridBase* Grid, ARandomTDTowerBase* TowerBase);

	TMap<ARandomTDTowerBase*, ARandomTDGridBase*> ListOfActiveTowerRefs; ///< List of tower actors in the world.

public:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Not used.
	virtual void Tick(float DeltaTime) override;
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief This function gets implemented by BP_TowerFactory and
	/// gets called from PC C++ class.
	/// 
	/// BP_TowerFactory has easy access to a variety of BP implemented
	/// towers that can be spawned.
	/// @param Grid The location where the tower will be spawned.
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Tower")
	void SpawnTower(ARandomTDGridBase* Grid);
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Unselects all Towers so that none are highlighted & will not respond to "right-clicks"
	void UnselectAll();
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Selects a Tower to start listening to "right-clicks"
	void Select(ARandomTDTowerBase* Tower);
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Destroys a tower.
	/// @remark This function is bound to the TowerBase's delegate function. That means
	/// this function is called when TowerBase calls its delegate. This is not directly called.
	/// @param Tower Tower to be deleted.
	/// @todo This function also deletes the tower/grid key/value from the map and it sets the grid
	/// to valid... idk if this is the right place for that but it will do for now.
	void DestroyTower(ARandomTDTowerBase* Tower);
};
