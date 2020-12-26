// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerFactory.generated.h"

/////////////////////////////////////////////////////////////////////////////////////
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
	ARandomTDTowerFactory();

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	virtual void BeginPlay() override;

public:
	/////////////////////////////////////////////////////////////////////////////////////
	virtual void Tick(float DeltaTime) override;

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief This function gets implemented by BP_TowerFactory and
	/// gets called from PC C++ class.
	/// 
	/// BP_TowerFactory has easy access to a variety of BP implemented
	/// towers that can be spawned.
	/// @param Grid The location where the tower will be spawned.
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Tower")
	class ARandomTDTowerCharacter* SpawnTower(class ARandomTDGridBase* Grid);
};
