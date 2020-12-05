// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindEnemy.generated.h"

/**
 * 
 */
UCLASS()
class RANDOMTD_API UBTTask_FindEnemy : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

public:
	//////////////////////////////////////////////////////////////////////////
	void FindClosestEnemy(AAIController* TowerController, APawn* TowerActor);

	//////////////////////////////////////////////////////////////////////////
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	//////////////////////////////////////////////////////////////////////////
	FName GetSelectedEnemyActorKey() const;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector EnemyActorKey;
};
//////////////////////////////////////////////////////////////////////////
FORCEINLINE FName UBTTask_FindEnemy::GetSelectedEnemyActorKey() const
{
	return EnemyActorKey.SelectedKeyName;
}
