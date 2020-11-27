// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomTDEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RandomTDEnemyCharacter.h"
#include "RandomTDPathSpline.h"
#include "RandomTD.h"

FOnDestroyEnemy ARandomTDEnemyController::DestroyEnemyEvent;

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDEnemyController::ARandomTDEnemyController()
  : BBKey_EnemyActor(TEXT("EnemyActor"))
  , BBKey_Waypoint(TEXT("NextWaypoint"))
  , BBKey_PendingKill(TEXT("IsPendingKill"))

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

  EnemyRef = (ARandomTDEnemyCharacter*)InPawn;
  // initialize values in blackboard
  BlackboardComponentRef->SetValueAsObject(BBKey_EnemyActor, InPawn);
  BlackboardComponentRef->SetValueAsVector(BBKey_Waypoint, FVector());
  BlackboardComponentRef->SetValueAsBool(BBKey_PendingKill, false);

  // start
  RunBehaviorTree(BTAssetRef);
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyController::NotifyDespawn()
{
  DestroyEnemyEvent.Execute(EnemyRef);
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyController::Tick(float DeltaTime)
{
  // Necessary to get pawn to rotate
  Super::Tick(DeltaTime);

  // check if actor reached the end of path
  if (EnemyRef && EnemyRef->FinishedPath)
  {
    // stop enemy calls
    BlackboardComponentRef->SetValueAsBool(BBKey_PendingKill, true);

    // next tick call destroy
    GetWorldTimerManager().SetTimerForNextTick(this, &ARandomTDEnemyController::NotifyDespawn);
  }
}
