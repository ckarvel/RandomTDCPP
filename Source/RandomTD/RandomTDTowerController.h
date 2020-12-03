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

protected:
	///////////////////////////////////////////////////////////////////////////
	void BeginPlay() override;

	///////////////////////////////////////////////////////////////////////////
	virtual void OnPossess(APawn* InPawn) override;

	///////////////////////////////////////////////////////////////////////////
	virtual void Tick(float DeltaTime) override;

	///////////////////////////////////////////////////////////////////////////
	UFUNCTION()
	void TargetUpdated(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(EditAnywhere, Category = "TowerBase")
	class UBlackboardData* BlackboardData;

	UPROPERTY(EditAnywhere, Category = "TowerBase")
	class UBehaviorTree* BTAssetRef;

	UPROPERTY(EditAnywhere, Category = "TowerBase")
	FName BBKey_AttackTarget;

	class ARandomTDTowerCharacter* TowerRef;
};
