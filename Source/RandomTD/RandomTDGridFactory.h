// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomTDGridFactory.generated.h"

///////////////////////////////////////////////////////////////////////////
/// @class ARandomTDGridFactory 
/// @brief Handles spawning/despawning grids.
/// 
/// Used as an interface for PlayerController/TowerFactory to
/// gain access to specific grids.
UCLASS()
class RANDOMTD_API ARandomTDGridFactory : public AActor
{
	GENERATED_BODY()
	
public:
	///////////////////////////////////////////////////////////////////////////
	///@brief Sets default values
	ARandomTDGridFactory();

protected:
	///////////////////////////////////////////////////////////////////////////
	/// @see ARandomTDPlayerController::BeginPlay()
	virtual void BeginPlay() override;

public:	
	///////////////////////////////////////////////////////////////////////////
	/// @brief Not used.
	virtual void Tick(float DeltaTime) override;

	///////////////////////////////////////////////////////////////////////////
	/// @brief BP-callable function to create an array of GridBase
	/// actors.
	/// 
	/// Called by BP_GridFactory in BeginPlay().
	/// The actor that needs to spawn in the world is the blueprint
	/// derived class of ARandomTDGridBase. BP_GridBase contains the art (mesh/materials).
	/// Another way this can be done is by using the ContructorHelper to find the
	/// blueprint asset but I think I like this better.
	/// 
	/// @param BP_GridBaseClass BP_GridBase class type needed to spawn the actor.
	UFUNCTION(BlueprintCallable, Category = Grid)
	void SetupGridArray(TSubclassOf<ARandomTDGridBase> BP_GridBaseClass);

	UFUNCTION(BlueprintImplementableEvent, Category = Grid)
	void SetGridValidity(ARandomTDGridBase* Grid, FVector Location);

public:
	UPROPERTY(Category = GridSetup, EditAnywhere)
	int Grid_X; ///< The number of rows in the grid array

	UPROPERTY(Category = GridSetup, EditAnywhere)
	int Grid_Y; ///< The number of columns in the grid array

	UPROPERTY(Category = GridSetup, VisibleAnywhere, BlueprintReadOnly)
	int GridSize; ///< The width/height (its a square) of each grid

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerController)
	TSubclassOf<ARandomTDGridBase> GridBaseClass; ///< Class type for the blueprint derived class
																			  ///< of ARandomTDGridBase. Used to spawn the grid actors.

protected:
	TArray<ARandomTDGridBase*> GridBaseList; ///< List of grid actors in the world.
};
