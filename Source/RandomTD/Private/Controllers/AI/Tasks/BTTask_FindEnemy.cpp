// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AI/Tasks/BTTask_FindEnemy.h"

#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Math/Vector.h"
#include "AIController.h"
#include "Controllers/TowerController.h"
#include "RandomTD/RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
UBTTask_FindEnemy::UBTTask_FindEnemy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Find enemy";
	bNotifyTick = true;

	// set allowed types for keys
	EnemyActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindEnemy, EnemyActorKey), AActor::StaticClass());
}

/////////////////////////////////////////////////////////////////////////////////////
EBTNodeResult::Type UBTTask_FindEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* TowerController = OwnerComp.GetAIOwner();
	if (TowerController == nullptr || TowerController->GetPawn() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	APawn* TowerActor = TowerController->GetPawn();
	if (TowerActor == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FindClosestEnemy(TowerController, TowerActor);

	return EBTNodeResult::Succeeded;
}

/////////////////////////////////////////////////////////////////////////////////////
void UBTTask_FindEnemy::FindClosestEnemy(AAIController* TowerController, APawn* TowerActor)
{
	// find all active hostile enemies near TowerActor
	TArray<AActor*> EnemyActors;
	TowerController->PerceptionComponent->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), EnemyActors);
	
	// look for enemy closest to tower
	AActor* FoundEnemy = nullptr;
	float MinimumDist = TNumericLimits<float>::Max();
	for (int i = 0; i < EnemyActors.Num(); i++)
	{
		float Dist = FVector::Distance(TowerActor->GetActorLocation(), EnemyActors[i]->GetActorLocation());
		if (MinimumDist > Dist)
		{
			// this is the shortest dist so far so save distance and the enemy
			MinimumDist = Dist;
			FoundEnemy = EnemyActors[i];
		}
		else
		{
			// this enemy is further away from the tower
			// if list is in order of enemies perceived, I could do early exit here. Idk though.
			// for now do nothing.
		}
	}

	// enemy not found
	if (!FoundEnemy)
		return;

	// enemy found, update tower controller
	if (ARandomTDTowerController* TC = Cast<ARandomTDTowerController>(TowerController))
	{
		TC->OnTargetUpdate(FoundEnemy);
	}
	else
	{
		UE_LOG(LogRandomTD, Error, TEXT("UBTTask_FindEnemy::FindClosestEnemy: Can't cast TowerController!"));
	}
}