// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindNextWaypoint.generated.h"

UCLASS()
class RANDOMTD_API UBTTask_FindNextWaypoint : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

public:
	/** get name of selected blackboard key */
	FName GetSelectedNextWaypointKey() const;
	FName GetSelectedEnemyActorKey() const;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector NextWaypointKey;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector EnemyActorKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
//////////////////////////////////////////////////////////////////////////
FORCEINLINE FName UBTTask_FindNextWaypoint::GetSelectedNextWaypointKey() const
{
	return NextWaypointKey.SelectedKeyName;
}
//////////////////////////////////////////////////////////////////////////
FORCEINLINE FName UBTTask_FindNextWaypoint::GetSelectedEnemyActorKey() const
{
	return EnemyActorKey.SelectedKeyName;
}
/////////////////////////////////////////////////////////////////////////////////////
