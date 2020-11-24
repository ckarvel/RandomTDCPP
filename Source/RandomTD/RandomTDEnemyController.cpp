// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomTDEnemyController.h"
#include "RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDEnemyController::ARandomTDEnemyController()
{
#ifdef UE_BUILD_DEBUG
UE_LOG(LogRandomTD, Log, TEXT("ARandomTDEnemyController::Constructor"));
#endif
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyController::BeginPlay()
{
  Super::BeginPlay();
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyController::OnPossess(APawn* InPawn)
{
  // necessary to allow BP to run behavior tree
  Super::OnPossess(InPawn);
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyController::Tick(float DeltaTime)
{
  // Necessary to get pawn to rotate
  Super::Tick(DeltaTime);
}
