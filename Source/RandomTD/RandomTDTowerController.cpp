// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomTDTowerController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "RandomTDTowerCharacter.h"
#include "RandomTD.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActorPerceptionUpdatedDelegate, AActor*, Actor, FAIStimulus, Stimulus);

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDTowerController::ARandomTDTowerController()
{
  SetGenericTeamId(FGenericTeamId(1)); // if actors have two different ids, they are "hostile"

  // create blackboard data asset
  Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
  Blackboard->InitializeBlackboard(*BlackboardData);

  // perception
  PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
  UAISenseConfig_Sight* Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");

  // only sense enemies
  Sight->DetectionByAffiliation.bDetectEnemies = true;
  Sight->DetectionByAffiliation.bDetectNeutrals = false;
  Sight->DetectionByAffiliation.bDetectFriendlies = false;

  PerceptionComponent->ConfigureSense(*Sight);
}

/////////////////////////////////////////////////////////////////////////////////////
ETeamAttitude::Type ARandomTDTowerController::GetTeamAttitudeTowards(const AActor& Other) const
{
  if (const APawn* OtherPawn = Cast<APawn>(&Other)) {

    if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
    {
      return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
    }
  }
  return ETeamAttitude::Neutral;
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerController::BeginPlay()
{
  Super::BeginPlay();

  // bind functions to delegates
  PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ARandomTDTowerController::TargetUpdated);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerController::OnPossess(APawn* InPawn)
{
  // necessary to allow BP to run behavior tree
  Super::OnPossess(InPawn);

  TowerRef = (ARandomTDTowerCharacter*)InPawn;

  // start behavior tree
  RunBehaviorTree(BTAssetRef);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerController::Tick(float DeltaTime)
{
  // Necessary to get pawn to rotate
  Super::Tick(DeltaTime);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerController::TargetUpdated(AActor* Actor, FAIStimulus Stimulus)
{
  if (!Stimulus.WasSuccessfullySensed())
    return; // if actor not sensed, return

  UObject* Target = Blackboard->GetValueAsObject(BBKey_AttackTarget);
  if (Target != nullptr)
    return; // if we're already attacking, return
  
  // set our new enemy target
  Blackboard->SetValueAsObject(BBKey_AttackTarget, Actor);
}