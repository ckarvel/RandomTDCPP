// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_FindNextWaypoint.h"
#include "RandomTD/RandomTDEnemyCharacter.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

/////////////////////////////////////////////////////////////////////////////////////
UBTTask_FindNextWaypoint::UBTTask_FindNextWaypoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Find next waypoint";
	bNotifyTick = true;

	// set allowed types for keys
	NextWaypointKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindNextWaypoint, NextWaypointKey));
	EnemyActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindNextWaypoint, EnemyActorKey), AActor::StaticClass());
}
/////////////////////////////////////////////////////////////////////////////////////
EBTNodeResult::Type UBTTask_FindNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == NULL || AIController->GetPawn() == NULL)
	{
		return EBTNodeResult::Failed;
	}
	ARandomTDEnemyCharacter* Enemy = (ARandomTDEnemyCharacter*)AIController->GetPawn();
	if (Enemy == NULL)
	{
		return EBTNodeResult::Failed;
	}
	FVector Waypoint = Enemy->GetNextWaypoint();
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedNextWaypointKey(), Waypoint);
	
	return EBTNodeResult::Succeeded;
}
/////////////////////////////////////////////////////////////////////////////////////
