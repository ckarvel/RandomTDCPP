// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridBase.h"
#include "TowerBase.h"

#include "TowerFactory.generated.h"

/// @class ATowerFactory 
/// @brief Handles spawning/despawning towers.
/// 
/// Used as an interface for PlayerController to
/// gain access to specific towers.
UCLASS()
class RANDOMTD_API ATowerFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	///@brief Sets default values
	ATowerFactory();

protected:
	/// @see ARandomTDPlayerController::BeginPlay()
	virtual void BeginPlay() override;

public:	
	/// @brief Not used.
	virtual void Tick(float DeltaTime) override;

	/// @brief This function gets implemented by BP_TowerFactory and
	/// gets called from C++ implemented class.
	/// 
	/// BP_TowerFactory has easy access to a variety of BP implemented
	/// towers that can be spawned.
	/// @param Grid The location where the tower will be spawned.
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Tower")
	void SpawnTower(AGridBase* Grid);

	/// @brief Called by BP_TowerFactory so it can provide us with a reference
	/// to the newly spawned tower.
	UFUNCTION(BlueprintCallable, Category = "Tower")
	void AddNewTowerToList(AGridBase* Grid, ATowerBase* TowerBase);

	ATowerBase* GetSelected();

	/////////////////////////////////////////////////////////////////////////////////////
	//																	Variables
	/////////////////////////////////////////////////////////////////////////////////////
protected:
	TMap<AGridBase*, ATowerBase*> ListOfActiveTowerRefs; ///< List of tower actors in the world.
};
