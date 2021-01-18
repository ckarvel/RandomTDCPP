// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelMgmtComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelStart, int, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelSecondElapsed, int, ElapsedTime);
/////////////////////////////////////////////////////////////////////////////////////
/// BlueprintType = Exposes this class as a type that can be used for variables in Blueprints.
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RANDOMTD_API ULevelMgmtComponent : public UActorComponent
{
	GENERATED_BODY()

private:
  FTimerHandle LevelCountTimerHandle; ///< manage level time
  FTimerHandle LevelElapsedTimerHandle; ///< manage notification interval

  int SecondsPerLevel; ///< Defines level time length in seconds.
  int PreLevelSeconds; ///< Defines pre-level time length in seconds.
  int CurrentLevel; ///< The current level in the game.

protected:
  /////////////////////////////////////////////////////////////////////////////////////
  /// @brief Starts level timers
  /// @see StartPreLevelTimer
  /// @see StartElapsedTimer
  virtual void BeginPlay() override;

  /////////////////////////////////////////////////////////////////////////////////////
  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  /////////////////////////////////////////////////////////////////////////////////////
  /// @brief Starts timer for the initial level before the game actually starts (pre-level).
  /// @remark Reference stored @ref LevelCountTimerHandle
  void StartPreLevelTimer();

  /////////////////////////////////////////////////////////////////////////////////////
  /// @brief This starts the @a real game timer that manages level changes.
  /// @details Every @ref SecondsPerLevel a new level starts and @ref OnLevelChange is called.
  void StartLevelTimer();

  /////////////////////////////////////////////////////////////////////////////////////
  /// @brief Starts timer that broadcasts every second how much time has elapsed since
  /// the start of the current round.
  /// @remark Reference stored @ref LevelElapsedTimerHandle
  void StartElapsedTimer();

  /////////////////////////////////////////////////////////////////////////////////////
  /// @brief Broadcasts LevelStartEvent with the new @ref CurrentLevel value.
  void OnLevelChange();

  /////////////////////////////////////////////////////////////////////////////////////
  /// @brief Broadcasts LevelSecondElapsedEvent with how many seconds have elapsed since
  /// current level start.
  void OnLevelSecondElapsed();

public:
  /////////////////////////////////////////////////////////////////////////////////////
  ULevelMgmtComponent();

  /////////////////////////////////////////////////////////////////////////////////////
  /// @brief Returns the length of time for each level in seconds.
  UFUNCTION(BlueprintCallable, Category = "Getters")
  int GetSecondsPerLevel() { return SecondsPerLevel; }

  /////////////////////////////////////////////////////////////////////////////////////
  /// @brief Returns the length of time for the pre-level in seconds.
  UFUNCTION(BlueprintCallable, Category = "Getters")
  int GetPreLevelSeconds() { return PreLevelSeconds; }

  /////////////////////////////////////////////////////////////////////////////////////
  UFUNCTION(BlueprintCallable, Category = "Getters")
  int GetCurrentLevel() { return CurrentLevel; }

  UPROPERTY(BlueprintAssignable, Category = "Level Update")
  FOnLevelStart LevelStartEvent; ///< broadcasts level change

  UPROPERTY(BlueprintAssignable, Category = "Elapsed Time Update")
  FOnLevelSecondElapsed LevelSecondElapsedEvent; ///< broadcasts level elapsed seconds
};
