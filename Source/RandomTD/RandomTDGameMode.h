// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RandomTDGameMode.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnRoundStart, int);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRoundSecondElapsed, int);

UCLASS(minimalapi)
class ARandomTDGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	ARandomTDGameMode();

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void StartPlay() override;

	void StartPreRoundTimer();
	void StartRoundTimer();
	void StartElapsedTimer();
	void OnRoundChange();
	void OnRoundSecondElapsed();

	static int GetSecondsPerRound();
	static int GetPreRoundSeconds();
	// delegates
	static FOnRoundStart RoundStartEvent;
	static FOnRoundSecondElapsed RoundSecondElapsedEvent;

	static const int SecondsPerRound;
	static const int PreRoundSeconds;

protected:
	int CurrentRound;

	FTimerHandle RoundCountTimerHandle;
	FTimerHandle RoundElapsedTimerHandle;
};
