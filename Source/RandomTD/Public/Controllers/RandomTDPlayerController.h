// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RandomTDPlayerController.generated.h"

class ARandomTDPlayerCharacter;
class UTowerMgmtComponent;

///////////////////////////////////////////////////////////////////////////
/// @class ARandomTDPlayerController
/// @brief The PlayerController for Random TD
/// 
/// Handles player input
UCLASS()
class ARandomTDPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
  /////////////////////////////////////////////////////////////////////////////
  ///// @brief Called when right mouse button is pressed
  ///// 
  ///// Starts the character movement updates in Tick()
  void StartMoving() { bMoveToMouseCursor = true; }

  /////////////////////////////////////////////////////////////////////////////
  ///// @brief Called when right mouse button is released
  ///// 
  ///// Ends the character movement updates in Tick()
  ///// This is good for performance because character movement is only
  ///// being updated when the player clicks the right mouse button, instead
  ///// of unnecessarily updating pawn movement when the pawn is not moving!
  void StopMoving() { bMoveToMouseCursor = false; }

  ///////////////////////////////////////////////////////////////////////////
  /// @brief Zoom camera up and down based on AxisValue
  /// 
  /// Called every tick
  void MoveCameraUp(float AxisValue);

  ///////////////////////////////////////////////////////////////////////////
  /// @brief Pans the camera forward or backwards based on AxisValue
  /// 
  /// Called every tick
  /// @param AxisValue 1 Forward
  /// -1 Backwards
  /// 0 No movement
  void MoveCameraForward(float AxisValue);

  ///////////////////////////////////////////////////////////////////////////
  /// @brief Pans the camera right or left based on AxisValue
  /// 
  /// Called every tick
  /// @param AxisValue 1 Right
  /// -1 Left
  /// 0 No movement
  void MoveCameraRight(float AxisValue);

  bool bMoveToMouseCursor; ///< True to move character to cursor

protected:
  ///////////////////////////////////////////////////////////////////////////
  /// @brief Called when game starts or when spawned.
  /// 
  /// All actors in the level exist at this point so
  /// it is safe to store references to other actors here.
  void BeginPlay() override;

  ///////////////////////////////////////////////////////////////////////////
  /// @brief Handles elements of the game that requires
  /// an update every tick, e.g character movement.
  /// @param DeltaTime How much time has passed since the last tick
  virtual void PlayerTick(float DeltaTime) override;

  ///////////////////////////////////////////////////////////////////////////
  UFUNCTION(BlueprintImplementableEvent, Category = Tower)
  void CreateBasicTower();

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
  float CameraMovementSpeed; ///< How fast the camera pans

public:
	///////////////////////////////////////////////////////////////////////////
	/// @brief Set default mouse cursor settings.
	ARandomTDPlayerController();

  ///////////////////////////////////////////////////////////////////////////
  /// @brief  Setup bind actions and axis mappings.
  virtual void SetupInputComponent() override;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
  FVector CameraExtents;
};
