// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindNextWaypoint.generated.h"

UCLASS()
class RANDOMTD_API UBTTask_FindNextWaypoint : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

	/** get name of selected blackboard key */
	FName GetSelectedNextWaypointKey() const;
	FName GetSelectedPathActorKey() const;
	FName GetSelectedEnemyActorKey() const;

protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector NextWaypointKey;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector PathActorKey;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector EnemyActorKey;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
//////////////////////////////////////////////////////////////////////////
FORCEINLINE FName UBTTask_FindNextWaypoint::GetSelectedNextWaypointKey() const
{
	return NextWaypointKey.SelectedKeyName;
}
//////////////////////////////////////////////////////////////////////////
FORCEINLINE FName UBTTask_FindNextWaypoint::GetSelectedPathActorKey() const
{
	return PathActorKey.SelectedKeyName;
}
//////////////////////////////////////////////////////////////////////////
FORCEINLINE FName UBTTask_FindNextWaypoint::GetSelectedEnemyActorKey() const
{
	return EnemyActorKey.SelectedKeyName;
}