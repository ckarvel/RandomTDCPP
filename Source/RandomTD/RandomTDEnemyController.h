// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RandomTDEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class RANDOMTD_API ARandomTDEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	///////////////////////////////////////////////////////////////////////////
	/// @brief
	ARandomTDEnemyController();

protected:
	///////////////////////////////////////////////////////////////////////////
	/// @brief
	void BeginPlay() override;
	///////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void OnPossess(APawn* InPawn) override;
	///////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void Tick(float DeltaTime) override;

	class ARandomTDEnemyController* EnemyRef;
};
