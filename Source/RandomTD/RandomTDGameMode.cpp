// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomTDGameMode.h"
#include "RandomTDPlayerController.h"
#include "RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
// Define static fields
FOnRoundStart ARandomTDGameMode::RoundStartEvent;
FOnRoundSecondElapsed ARandomTDGameMode::RoundSecondElapsedEvent;
const int ARandomTDGameMode::SecondsPerRound = 60;
const int ARandomTDGameMode::PreRoundSeconds = 30;

int ARandomTDGameMode::GetSecondsPerRound() { return SecondsPerRound; }
int ARandomTDGameMode::GetPreRoundSeconds() { return PreRoundSeconds; }

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDGameMode::ARandomTDGameMode()
{
	PlayerControllerClass = ARandomTDPlayerController::StaticClass();
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDGameMode::StartPlay()
{
	Super::StartPlay();

	StartPreRoundTimer(); // timer for the first round
	StartElapsedTimer(); // timer to tell UI round time once a second
}

///////////////////////////////////////////////////////////////////////////////////////
void ARandomTDGameMode::StartPreRoundTimer()
{
	// set a timer until the real game starts
	// the initial delay is the pre round
	GetWorldTimerManager().SetTimer(RoundCountTimerHandle,
		this,
		&ARandomTDGameMode::StartRoundTimer,
		PreRoundSeconds, // if equal to 1, initial delay < 0
		false, // run once
		PreRoundSeconds); // initial delay (used as countdown for preround)
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDGameMode::StartRoundTimer()
{
	// start the real game timer
	GetWorldTimerManager().SetTimer(RoundCountTimerHandle,
		this,
		&ARandomTDGameMode::OnRoundChange,
		SecondsPerRound,
		true,
		0.0f); // initial delay used for smooth transition from prerounds

	// reset elapsed timer
	StartElapsedTimer();
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDGameMode::StartElapsedTimer()
{
	GetWorldTimerManager().SetTimer(RoundElapsedTimerHandle,
		this,
		&ARandomTDGameMode::OnRoundSecondElapsed,
		1.0f,
		true,
		0.0f);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDGameMode::OnRoundChange()
{
	CurrentRound++;
	RoundStartEvent.Broadcast(CurrentRound);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDGameMode::OnRoundSecondElapsed()
{
	// query the round count timer for how long until round changes
	float TimeElapsed = GetWorldTimerManager().GetTimerElapsed(RoundCountTimerHandle);
	int Seconds = FGenericPlatformMath::RoundToInt(TimeElapsed);

	RoundSecondElapsedEvent.Broadcast(Seconds);
}
