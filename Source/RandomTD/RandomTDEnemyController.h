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

	UPROPERTY(EditAnywhere, Category = "Enemy")
	class UBlackboardData* BlackboardAssetRef;
	UPROPERTY(EditAnywhere, Category = "Enemy")
	class UBlackboardComponent* BlackboardComponentRef;
	UPROPERTY(EditAnywhere, Category = "Enemy")
	class UBehaviorTree* BTAssetRef;
	UPROPERTY(EditAnywhere, Category = "Enemy")
	FName BBKey_EnemyActor;
	UPROPERTY(EditAnywhere, Category = "Enemy")
	FName BBKey_Waypoint;
};
