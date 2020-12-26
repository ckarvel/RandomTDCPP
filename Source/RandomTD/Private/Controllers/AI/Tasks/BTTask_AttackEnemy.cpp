// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AI/Tasks/BTTask_AttackEnemy.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

/////////////////////////////////////////////////////////////////////////////////////
UBTTask_AttackEnemy::UBTTask_AttackEnemy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Attack enemy";
	bNotifyTick = true;

	// set allowed types for keys
	EnemyActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_AttackEnemy, EnemyActorKey), AActor::StaticClass());
}

/////////////////////////////////////////////////////////////////////////////////////
EBTNodeResult::Type UBTTask_AttackEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr || AIController->GetPawn() == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	APawn* Pawn = AIController->GetPawn();
	if (Pawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	AActor* Enemy = (AActor*)OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedEnemyActorKey());
	UGameplayStatics::ApplyDamage(Enemy, 5.0, AIController, Pawn, nullptr);
	return EBTNodeResult::Succeeded;
}
