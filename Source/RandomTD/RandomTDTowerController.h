// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "GenericTeamAgentInterface.h"
#include "RandomTDTowerController.generated.h"

/**
 * 
 */
UCLASS()
class RANDOMTD_API ARandomTDTowerController : public AAIController
{
	GENERATED_BODY()
public:
	ARandomTDTowerController();

	///////////////////////////////////////////////////////////////////////////
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	///////////////////////////////////////////////////////////////////////////
	void OnTargetUpdate(AActor* Actor);

  ///////////////////////////////////////////////////////////////////////////
  void SetupBB(class UBlackboardData* BD, class UBehaviorTree* BT, FName Key);

protected:
	///////////////////////////////////////////////////////////////////////////
	void BeginPlay() override;

	///////////////////////////////////////////////////////////////////////////
	virtual void OnPossess(APawn* InPawn) override;

	///////////////////////////////////////////////////////////////////////////
	virtual void Tick(float DeltaTime) override;

	///////////////////////////////////////////////////////////////////////////
	/// @brief we dont need to worry about force updating targets here, that will
	/// be someone else's job... i think. Something involving PlayerController
	UFUNCTION()
	void PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	///////////////////////////////////////////////////////////////////////////
	// @warning I think this needs to be unbound when enemy dies
	void OnEnemyHealthUpdate(int RemainingEnemyHealth);

	///////////////////////////////////////////////////////////////////////////
	UFUNCTION()
	void OnEnemyDestroyed(AActor* Actor);

	UPROPERTY(EditAnywhere, Category = "TowerBase")
	class UBlackboardData* BlackboardData;

	UPROPERTY(EditAnywhere, Category = "TowerBase")
	class UBehaviorTree* BTAssetRef;

	UPROPERTY(EditAnywhere, Category = "TowerBase")
	FName BBKey_EnemyActor;

	class ARandomTDTowerCharacter* TowerRef;
	AActor* EnemyRef;
};
