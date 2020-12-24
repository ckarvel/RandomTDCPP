// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelManager.h"

///////////////////////////////////////////////////////////////////////////////////////
ALevelManager::ALevelManager()
: SecondsPerLevel(60)
, PreLevelSeconds(2)
{
	PrimaryActorTick.bCanEverTick = false; // no ticking
}

/////////////////////////////////////////////////////////////////////////////////////
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();

	StartPreLevelTimer(); // timer for the first round
	StartElapsedTimer(); // timer to tell UI round time once a second
}

/////////////////////////////////////////////////////////////////////////////////////
void ALevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

///////////////////////////////////////////////////////////////////////////////////////
void ALevelManager::StartPreLevelTimer()
{
	// set a timer until the real game starts
	// the initial delay is the pre round
	GetWorldTimerManager().SetTimer(LevelCountTimerHandle,
		this,
		&ALevelManager::StartLevelTimer,
		PreLevelSeconds, // if equal to 1, initial delay < 0
		false, // run once
		PreLevelSeconds); // initial delay (used as countdown for preround)
}

/////////////////////////////////////////////////////////////////////////////////////
void ALevelManager::StartLevelTimer()
{
	// start the real game timer
	GetWorldTimerManager().SetTimer(LevelCountTimerHandle,
		this,
		&ALevelManager::OnLevelChange,
		SecondsPerLevel,
		true,
		0.0f); // initial delay used for smooth transition from prerounds

	// reset elapsed timer
	StartElapsedTimer();
}

/////////////////////////////////////////////////////////////////////////////////////
void ALevelManager::StartElapsedTimer()
{
	GetWorldTimerManager().SetTimer(LevelElapsedTimerHandle,
		this,
		&ALevelManager::OnLevelSecondElapsed,
		1.0f,
		true,
		0.0f);
}

/////////////////////////////////////////////////////////////////////////////////////
void ALevelManager::OnLevelChange()
{
	CurrentLevel++;
	LevelStartEvent.Broadcast(CurrentLevel);
}

/////////////////////////////////////////////////////////////////////////////////////
void ALevelManager::OnLevelSecondElapsed()
{
	// query the round count timer for how long until round changes
	float TimeElapsed = GetWorldTimerManager().GetTimerElapsed(LevelCountTimerHandle);
	int Seconds = FGenericPlatformMath::RoundToInt(TimeElapsed);

	LevelSecondElapsedEvent.Broadcast(Seconds);
}
