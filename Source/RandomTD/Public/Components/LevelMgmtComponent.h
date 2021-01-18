// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LevelMgmtComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelStart, int, CurrentLevel);
/////////////////////////////////////////////////////////////////////////////////////
/// BlueprintType = Exposes this class as a type that can be used for variables in Blueprints.
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RANDOMTD_API ULevelMgmtComponent : public UActorComponent
{
  GENERATED_UCLASS_BODY()

private:
  float SecondsPerLevel; ///< Defines level time length in seconds.
  float PreLevelSeconds; ///< Defines pre-level time length in seconds.
  int CurrentLevel; ///< The current level in the game.

protected:
  /////////////////////////////////////////////////////////////////////////////////////
  /// @brief Starts timer for the initial level before the game actually starts (pre-level).
  /// @remark Reference stored @ref LevelCountTimerHandle
  void StartPreLevelTimer();

  /////////////////////////////////////////////////////////////////////////////////////
  /// @brief This starts the @a real game timer that manages level changes.
  /// @details Every @ref SecondsPerLevel a new level starts and @ref OnLevelChange is called.
  UFUNCTION()
  void StartLevelTimer();

  /////////////////////////////////////////////////////////////////////////////////////
  /// @brief Broadcasts LevelStartEvent with the new @ref CurrentLevel value.
  UFUNCTION()
  void OnLevelChange();

public:
  /////////////////////////////////////////////////////////////////////////////////////
  /// @brief Starts level timers
  /// @see StartPreLevelTimer
  /// @see StartElapsedTimer
  virtual void InitializeComponent() override;

  /////////////////////////////////////////////////////////////////////////////////////
  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  /////////////////////////////////////////////////////////////////////////////////////
  /// @brief Returns the length of time for each level in seconds.
  UFUNCTION(BlueprintCallable, Category = "Getters")
  float GetSecondsPerLevel() { return SecondsPerLevel; }

  /////////////////////////////////////////////////////////////////////////////////////
  /// @brief Returns the length of time for the pre-level in seconds.
  UFUNCTION(BlueprintCallable, Category = "Getters")
  float GetPreLevelSeconds() { return PreLevelSeconds; }

  /////////////////////////////////////////////////////////////////////////////////////
  UFUNCTION(BlueprintCallable, Category = "Getters")
  int GetCurrentLevel() { return CurrentLevel; }

  /////////////////////////////////////////////////////////////////////////////////////
  UPROPERTY(BlueprintReadOnly, Category = "Level Timer Handle")
  FTimerHandle LevelCountTimerHandle; ///< manage level time

  UPROPERTY(BlueprintAssignable, Category = "Level Update")
  FOnLevelStart LevelStartEvent; ///< broadcasts level change
};
