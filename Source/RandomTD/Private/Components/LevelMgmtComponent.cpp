// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LevelMgmtComponent.h"
#include "Kismet/KismetSystemLibrary.h"

/////////////////////////////////////////////////////////////////////////////////////
ULevelMgmtComponent::ULevelMgmtComponent()
  : SecondsPerLevel(60)
  , PreLevelSeconds(2)
{
	PrimaryComponentTick.bCanEverTick = false;
}

/////////////////////////////////////////////////////////////////////////////////////
void ULevelMgmtComponent::BeginPlay()
{
	Super::BeginPlay();

  StartPreLevelTimer(); // timer for the first round
  StartElapsedTimer(); // timer to tell UI round time once a second
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
    PreLevelSeconds, // if 1, initial delay < 0
    false, // run once
    PreLevelSeconds);  // initial delay (actual countdown)
}

/////////////////////////////////////////////////////////////////////////////////////
void ULevelMgmtComponent::StartLevelTimer()
{
  // start the real game timer
  LevelCountTimerHandle = UKismetSystemLibrary::K2_SetTimer(this,
    "OnLevelChange",
    SecondsPerLevel,
    true, // loop
    0.0f); // initial delay used for smooth transition

  // reset elapsed timer
  StartElapsedTimer();
}

/////////////////////////////////////////////////////////////////////////////////////
void ULevelMgmtComponent::StartElapsedTimer()
{
  LevelElapsedTimerHandle = UKismetSystemLibrary::K2_SetTimer(this,
    "OnLevelSecondElapsed",
    1.0f,
    true,
    0.0f);
}

/////////////////////////////////////////////////////////////////////////////////////
void ULevelMgmtComponent::OnLevelChange()
{
  CurrentLevel++;
  LevelStartEvent.Broadcast(CurrentLevel);
}

/////////////////////////////////////////////////////////////////////////////////////
void ULevelMgmtComponent::OnLevelSecondElapsed()
{
  // query the round count timer for how long until round changes
  float TimeElapsed = UKismetSystemLibrary::K2_GetTimerElapsedTimeHandle(this, LevelCountTimerHandle);
  int Seconds = FGenericPlatformMath::RoundToInt(TimeElapsed);

  LevelSecondElapsedEvent.Broadcast(Seconds);
}
