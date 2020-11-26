// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomTDEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDEnemyController::ARandomTDEnemyController()
  : BBKey_EnemyActor(TEXT("EnemyActor"))
  , BBKey_Waypoint(TEXT("NextWaypoint"))

{
//#ifdef UE_BUILD_DEBUG
//UE_LOG(LogRandomTD, Log, TEXT("ARandomTDEnemyController::Constructor"));
//#endif
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyController::BeginPlay()
{
  Super::BeginPlay();

  // create blackboard data asset
  UseBlackboard(BlackboardAssetRef, BlackboardComponentRef);
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyController::OnPossess(APawn* InPawn)
{
  // necessary to allow BP to run behavior tree
  Super::OnPossess(InPawn);

  // initialize values in blackboard
  BlackboardComponentRef->SetValueAsObject(BBKey_EnemyActor, InPawn);
  BlackboardComponentRef->SetValueAsVector(BBKey_Waypoint, FVector());

  // start
  RunBehaviorTree(BTAssetRef);
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyController::Tick(float DeltaTime)
{
  // Necessary to get pawn to rotate
  Super::Tick(DeltaTime);
}
