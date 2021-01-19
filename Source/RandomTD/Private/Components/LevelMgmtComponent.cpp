// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LevelMgmtComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "RandomTD/RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
ULevelMgmtComponent::ULevelMgmtComponent(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
  , SecondsPerLevel(60.0)
  , PreLevelSeconds(3.0)
{
  bWantsInitializeComponent = true;
  PrimaryComponentTick.bCanEverTick = false;
}

/////////////////////////////////////////////////////////////////////////////////////
void ULevelMgmtComponent::InitializeComponent()
{
  Super::InitializeComponent();

  StartPreLevelTimer(); // timer for the first round
}

/////////////////////////////////////////////////////////////////////////////////////
void ULevelMgmtComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

///////////////////////////////////////////////////////////////////////////////////////
void ULevelMgmtComponent::StartPreLevelTimer()
{
  // set a timer until the real game starts
  // the initial delay is the pre round
  LevelCountTimerHandle = UKismetSystemLibrary::K2_SetTimer(this,
    "StartLevelTimer",
    PreLevelSeconds,
    false); // run once
}

/////////////////////////////////////////////////////////////////////////////////////
void ULevelMgmtComponent::StartLevelTimer()
{
  // we'll only hit this once when we transition from prelevel
  OnLevelChange();

  // start the real game timer
  LevelCountTimerHandle = UKismetSystemLibrary::K2_SetTimer(this,
    "OnLevelChange",
    SecondsPerLevel,
    true); // loop
}

/////////////////////////////////////////////////////////////////////////////////////
void ULevelMgmtComponent::OnLevelChange()
{
  CurrentLevel++;
  LevelStartEvent.Broadcast(CurrentLevel);
}
