#pragma once

#include "CoreMinimal.h"
#include "LevelManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelStart, int);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelSecondElapsed, int);

UCLASS()
class RANDOMTD_API ALevelManager: public AActor
{
public:
	GENERATED_BODY()
	/////////////////////////////////////////////////////////////////////////////////////
	ALevelManager();

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Starts level timers
	/// @see StartPreLevelTimer
	/// @see StartElapsedTimer
	/////////////////////////////////////////////////////////////////////////////////////
	virtual void BeginPlay() override;

public:
	/////////////////////////////////////////////////////////////////////////////////////
	virtual void Tick(float DeltaTime) override;

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Starts timer for the initial round before the game actually starts (pre-round).
	/// @remark Reference stored @ref LevelCountTimerHandle
	void StartPreLevelTimer();

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Starts timer that broadcasts every second how much time has elapsed since
	/// the start of the current round.
	/// @remark Reference stored @ref LevelElapsedTimerHandle
	void StartElapsedTimer();

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief This starts the @a real game timer that manages round changes.
	/// @details Every @ref SecondsPerLevel a new round starts and @ref OnLevelChange is called.
	void StartLevelTimer();

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Broadcasts LevelStartEvent with the new @ref CurrentLevel value.
	void OnLevelChange();

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Broadcasts LevelSecondElapsedEvent with how many seconds have elapsed since
	/// current round start.
	void OnLevelSecondElapsed();

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Returns the length of time for each round in seconds.
	int GetSecondsPerLevel() { return SecondsPerLevel;  }

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Returns the length of time for the pre-round in seconds.
	int GetPreLevelSeconds() { return PreLevelSeconds; }

	FOnLevelStart LevelStartEvent; ///< Delegate that broadcasts every round change

	FOnLevelSecondElapsed LevelSecondElapsedEvent; ///< Delegate that broadcasts every
																												///< second during the round

	int SecondsPerLevel; ///< Defines round time length in seconds.

	int PreLevelSeconds; ///< Defines pre-round time length in seconds.

protected:
	int CurrentLevel; ///< The current round in the game.

	FTimerHandle LevelCountTimerHandle; ///< Timer handle used for managing rounds

	FTimerHandle LevelElapsedTimerHandle; ///< Timer handle used for round time
																				///< notification.
};
