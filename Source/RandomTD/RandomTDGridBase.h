// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomTDGridBase.generated.h"

UCLASS()
class RANDOMTD_API ARandomTDGridBase : public AActor
{
	GENERATED_BODY()
	
public:	
	/////////////////////////////////////////////////////////////////////////////////////
	///@brief Setup box collision and static mesh components.
	ARandomTDGridBase();

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Setup dynamic material which will allow us to change
	/// colors during runtime.
	/// @see ARandomTDPlayerController::BeginPlay()
	virtual void BeginPlay() override;

public:	
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Not used.
	virtual void Tick(float DeltaTime) override;
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	void SetValid() { bIsValidGrid = true;  }
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	void SetInvalid() { bIsValidGrid = false; }
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	bool IsValid() { return bIsValidGrid; }

protected:
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
	bool bIsValidGrid; ///< If true, a tower can be placed on top of this grid.

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
	FLinearColor ValidTileColor; ///< The color for a valid highlight. Default: green

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
	FLinearColor InvalidTileColor; ///< The color for an invalid highlight. Default: red

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh; ///< How the grid will look in the world.
																		///< Is set to basic "Plane" shape.

	UPROPERTY(Category = Grid, VisibleAnywhere, BlueprintReadWrite)
	class UMaterialInstanceDynamic* DynamicMaterial; ///< Material that can be changed during
																						 ///< runtime. This is an instance based off
																						 /// of @c ParentMaterial.
	UPROPERTY(Category = Grid, VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxComponent; ///< Collision component required to have
															 ///< the grid act like part of the floor.
															 ///< (Can character step on this? Yes)
};
