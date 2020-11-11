// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridBase.h"
#include "GridFactory.generated.h"

/// @class AGridFactory 
/// @brief Handles spawning/despawning grids.
/// 
/// Used as an interface for PlayerController/TowerFactory to
/// gain access to specific grids.
UCLASS()
class RANDOMTD_API AGridFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	///@brief Sets default values
	AGridFactory();

protected:
	/// @see ARandomTDPlayerController::BeginPlay()
	virtual void BeginPlay() override;

public:	
	/// @brief Not used.
	virtual void Tick(float DeltaTime) override;
	
	AGridBase* GetSelected();
	/// @brief BP-callable function to create an array of GridBase
	/// actors.
	/// 
	/// Called by BP_GridFactory in BeginPlay().
	/// The actor that needs to spawn in the world is the blueprint
	/// derived class of AGridBase. BP_GridBase contains the art (mesh/materials).
	/// Another way this can be done is by using the ContructorHelper to find the
	/// blueprint asset but I think I like this better.
	/// 
	/// @param BP_GridBaseClass BP_GridBase class type needed to spawn the actor.
	UFUNCTION(BlueprintCallable, Category = Grid)
	void SetupGridArray(TSubclassOf<AGridBase> BP_GridBaseClass);

	/////////////////////////////////////////////////////////////////////////////////////
	//																	Variables
	/////////////////////////////////////////////////////////////////////////////////////

public:  
	UPROPERTY(Category = GridSetup, EditAnywhere)
	int Grid_X; ///< The number of rows in the grid array
	UPROPERTY(Category = GridSetup, EditAnywhere)
	int Grid_Y; ///< The number of columns in the grid array
	UPROPERTY(Category = GridSetup, VisibleAnywhere, BlueprintReadOnly)
	int GridSize; ///< The width/height (its a square) of each grid

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerController)
	TSubclassOf<AGridBase> GridBaseClass; ///< Class type for the blueprint derived class
																			  ///< of AGridBase. Used to spawn the grid actors.
protected:
	TArray<AGridBase*> GridBaseList; ///< List of grid actors in the world.
};
