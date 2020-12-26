// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TowerController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Characters/TowerCharacter.h"
#include "Characters/EnemyCharacter.h"
#include "RandomTD/RandomTD.h"

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

  // set sight radius
  Sight->SightRadius = 500.0;
  // maximum radius where we lose enemies
  Sight->LoseSightRadius = 501.0;
  // angle character can see relative to forward vector not whole range
  Sight->PeripheralVisionAngleDegrees = 180.0;
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
  PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ARandomTDTowerController::PerceptionUpdated);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerController::OnPossess(APawn* InPawn)
{
  // necessary to allow BP to run behavior tree
  Super::OnPossess(InPawn);

  // @todo save so I don't need to be dynamic casting later on. benefits??
  TowerRef = (ARandomTDTowerCharacter*)InPawn;

  // start behavior tree
  RunBehaviorTree(BTAssetRef);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerController::Tick(float DeltaTime)
{
  // necessary to get pawn to rotate
  Super::Tick(DeltaTime);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
  if (EnemyRef == nullptr)
    return; // this will get set by BTTask_FindEnemy

  if (EnemyRef != Actor)
    return; // this isn't our target
 
  if (!Stimulus.WasSuccessfullySensed()) // is our target out of range?
  {
    OnEnemyDestroyed(nullptr); // out of range so remove
  }
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerController::OnTargetUpdate(AActor* Enemy)
{
  if (Enemy == nullptr)
    return; // just in case...

  // store reference
  EnemyRef = Enemy;

  // set focus so that tower can rotate and face the enemy at the same time.
  SetFocus(EnemyRef, EAIFocusPriority::Gameplay);

  // set blackboard enemy key
  Blackboard->SetValueAsObject(BBKey_EnemyActor, EnemyRef);

  // bind to enemy delegates
  // has to be unique here because this function could be bound multiple times due to enemies getting
  // in and out of range.
  EnemyRef->OnDestroyed.AddUniqueDynamic(this, &ARandomTDTowerController::OnEnemyDestroyed);

  ARandomTDEnemyCharacter* DerivedEnemy = Cast<ARandomTDEnemyCharacter>(EnemyRef);
  if (DerivedEnemy == nullptr)
  {
    UE_LOG(LogRandomTD, Error, TEXT("ARandomTDTowerController::OnTargetUpdate: Casting Actor failed!"));
    return;
  }
  // get notified when enemy's health changes
  DerivedEnemy->OnHealthChangeEvent.AddUObject(this, &ARandomTDTowerController::OnEnemyHealthUpdate);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerController::OnEnemyHealthUpdate(int RemainingEnemyHealth)
{
  // do something fancy
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerController::OnEnemyDestroyed(AActor* Actor)
{
  // reset our data
  EnemyRef = nullptr;

  // I think ai does this on its own but... just in case
  ClearFocus(EAIFocusPriority::Gameplay);

  // notify blackboard that our target is dead
  Blackboard->SetValueAsObject(BBKey_EnemyActor, nullptr);
}
