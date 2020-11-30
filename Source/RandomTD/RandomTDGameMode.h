// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RandomTDGameMode.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnRoundStart, int);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRoundSecondElapsed, int);

///////////////////////////////////////////////////////////////////////////
/// @class ARandomTDGameMode 
/// @brief Handles game rules.
/// @details Manages game rounds.
UCLASS(minimalapi)
class ARandomTDGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/////////////////////////////////////////////////////////////////////////////////////
	ARandomTDGameMode();

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Starts round timers
	/// @see StartPreRoundTimer
	/// @see StartElapsedTimer
	virtual void StartPlay() override;

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Starts timer for the initial round before the game actually starts (pre-round).
	/// @remark Reference stored @ref RoundCountTimerHandle
	void StartPreRoundTimer();

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Starts timer that broadcasts every second how much time has elapsed since
	/// the start of the current round.
	/// @remark Reference stored @ref RoundElapsedTimerHandle
	void StartElapsedTimer();

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief This starts the @a real game timer that manages round changes.
	/// @details Every @ref SecondsPerRound a new round starts and @ref OnRoundChange is called.
	void StartRoundTimer();
	
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Broadcasts RoundStartEvent with the new @ref CurrentRound value.
	void OnRoundChange();
	
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Broadcasts RoundSecondElapsedEvent with how many seconds have elapsed since
	/// current round start.
	void OnRoundSecondElapsed();

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Returns the length of time for each round in seconds.
	static int GetSecondsPerRound();

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Returns the length of time for the pre-round in seconds.
	static int GetPreRoundSeconds();

	static FOnRoundStart RoundStartEvent; ///< Delegate that broadcasts every round change
	
	static FOnRoundSecondElapsed RoundSecondElapsedEvent; ///< Delegate that broadcasts every
																												///< second during the round

	static const int SecondsPerRound; ///< Defines round time length in seconds.
	
	static const int PreRoundSeconds; ///< Defines pre-round time length in seconds.

protected:
	int CurrentRound; ///< The current round in the game.

	FTimerHandle RoundCountTimerHandle; ///< Timer handle used for managing rounds

	FTimerHandle RoundElapsedTimerHandle; ///< Timer handle used for round time
																				///< notification.
};
