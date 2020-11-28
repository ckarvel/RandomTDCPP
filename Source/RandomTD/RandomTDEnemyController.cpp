// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomTDEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RandomTDEnemyCharacter.h"
#include "RandomTDPathSpline.h"
#include "RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDEnemyController::ARandomTDEnemyController()
  : BBKey_EnemyActor(TEXT("EnemyActor"))
  , BBKey_Waypoint(TEXT("NextWaypoint"))
  , BBKey_PendingKill(TEXT("IsPendingKill"))

{
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyController::BeginPlay()
{
  Super::BeginPlay();

  // create blackboard data asset
  UseBlackboard(BlackboardAssetRef, BlackboardComponentRef);

  // [state change == finished path] or [state change == dead] delegate
  ARandomTDEnemyCharacter::OnStateChangeEvent.AddUObject(this, &ARandomTDEnemyController::OnEnemyStateChange);
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

  // start behavior tree
  RunBehaviorTree(BTAssetRef);
}
/////////////////////////////////////////////////////////////////////////////////////
/// @todo could we also use do this pause the behavior tree when enemy is frozen??? maybe!!
void ARandomTDEnemyController::OnEnemyStateChange(ARandomTDEnemyCharacter* Enemy)
{
  if (EnemyRef != Enemy)
    return; // not my pawn

  // we got an update from our pawn, if pawn is finished path or dead
  // tell blackboard to stop
  BlackboardComponentRef->SetValueAsBool(BBKey_PendingKill, true);
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyController::Tick(float DeltaTime)
{
  // Necessary to get pawn to rotate
  Super::Tick(DeltaTime);
}
