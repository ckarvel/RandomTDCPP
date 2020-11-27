// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RandomTDEnemyController.generated.h"

class ARandomTDEnemyCharacter;
DECLARE_DELEGATE_OneParam(FOnDestroyEnemy, ARandomTDEnemyCharacter*);

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
	static FOnDestroyEnemy DestroyEnemyEvent;

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
	class UBlackboardData* BlackboardAssetRef;
	UPROPERTY(EditAnywhere, Category = "EnemyBase")
	class UBlackboardComponent* BlackboardComponentRef;
	UPROPERTY(EditAnywhere, Category = "EnemyBase")
	class UBehaviorTree* BTAssetRef;
	UPROPERTY(EditAnywhere, Category = "EnemyBase")
	FName BBKey_EnemyActor;
	UPROPERTY(EditAnywhere, Category = "EnemyBase")
	FName BBKey_Waypoint;
	UPROPERTY(EditAnywhere, Category = "EnemyBase")
	FName BBKey_PendingKill;
private:
	void NotifyDespawn();

	ARandomTDEnemyCharacter* EnemyRef;
};
