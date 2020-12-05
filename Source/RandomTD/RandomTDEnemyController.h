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

	///////////////////////////////////////////////////////////////////////////
	/// @brief
	void OnEnemyDestroyed();

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

	UPROPERTY(EditAnywhere, Category = "EnemyBase")
	class UBlackboardData* BlackboardData;
	
	UPROPERTY(EditAnywhere, Category = "EnemyBase")
	class UBehaviorTree* BTAssetRef;
	
	UPROPERTY(EditAnywhere, Category = "EnemyBase")
	FName BBKey_EnemyActor;
	
	UPROPERTY(EditAnywhere, Category = "EnemyBase")
	FName BBKey_Waypoint;
	
	UPROPERTY(EditAnywhere, Category = "EnemyBase")
	FName BBKey_PendingKill;

	class ARandomTDEnemyCharacter* EnemyRef;
};
