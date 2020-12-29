// Fill out your copyright notice in the Description page of Project Settings.

#include "Managers/LevelManager.h"

/////////////////////////////////////////////////////////////////////////////////////
ULevelManager::ULevelManager(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
  , SecondsPerLevel(60)
  , PreLevelSeconds(2)
{
}

/////////////////////////////////////////////////////////////////////////////////////
void ULevelManager::StartTimers()
{
  StartPreLevelTimer(); // timer for the first round
  StartElapsedTimer(); // timer to tell UI round time once a second
}

/////////////////////////////////////////////////////////////////////////////////////
void ULevelManager::SetTimerManager(FTimerManager* TimerManager)
{
	OwningTimerManager = TimerManager;
}

///////////////////////////////////////////////////////////////////////////////////////
void ULevelManager::StartPreLevelTimer()
{
	// set a timer until the real game starts
	// the initial delay is the pre round
	OwningTimerManager->SetTimer(LevelCountTimerHandle,
		this,
		&ULevelManager::StartLevelTimer,
		PreLevelSeconds, // if equal to 1, initial delay < 0
		false, // run once
		PreLevelSeconds); // initial delay (used as countdown for preround)
}

/////////////////////////////////////////////////////////////////////////////////////
void ULevelManager::StartLevelTimer()
{
	//// start the real game timer
	OwningTimerManager->SetTimer(LevelCountTimerHandle,
		this,
		&ULevelManager::OnLevelChange,
		SecondsPerLevel,
		true,
		0.0f); // initial delay used for smooth transition from prerounds

	// reset elapsed timer
	StartElapsedTimer();
}

/////////////////////////////////////////////////////////////////////////////////////
void ULevelManager::StartElapsedTimer()
{
  OwningTimerManager->SetTimer(LevelElapsedTimerHandle,
    this,
    &ULevelManager::OnLevelSecondElapsed,
    1.0f,
    true,
    0.0f);
}

/////////////////////////////////////////////////////////////////////////////////////
void ULevelManager::OnLevelChange()
{
	CurrentLevel++;
	LevelStartEvent.Broadcast(CurrentLevel);
}

/////////////////////////////////////////////////////////////////////////////////////
void ULevelManager::OnLevelSecondElapsed()
{
	// query the round count timer for how long until round changes
	float TimeElapsed = OwningTimerManager->GetTimerElapsed(LevelCountTimerHandle);
	int Seconds = FGenericPlatformMath::RoundToInt(TimeElapsed);

	LevelSecondElapsedEvent.Broadcast(Seconds);
}
