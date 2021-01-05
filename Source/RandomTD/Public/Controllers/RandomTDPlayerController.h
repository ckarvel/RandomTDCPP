// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RandomTDPlayerController.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FInteractEvent, FHitResult*);

class ACameraActor;
class UMainGameUserWidget;
class UPropManager;
class UTDCameraManager;
class UTowerManager;
class ARandomTDPlayerCharacter;

/// @class ARandomTDPlayerController
/// @brief The PlayerController for Random TD
/// 
/// Handles player input
UCLASS()
class ARandomTDPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
  ///////////////////////////////////////////////////////////////////////////
  /// @brief Called when player presses the left mouse button
  /// 
  /// Multiple behaviors depending existing actors
  /// @todo Figure out behaviors
  void OnInteractPressed();

  ///////////////////////////////////////////////////////////////////////////
  /// @brief Called when player releases the left mouse button
  /// @todo Is this the right function for drag-selection?
  //void OnInteractReleased();

  UPropManager* MyPropManager;
  UTowerManager* MyTowerManager;
  UTDCameraManager* MyCameraManager;
  ARandomTDPlayerCharacter* MyPawn;

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

  UPROPERTY(BlueprintReadWrite, Category = "Base")
  UMainGameUserWidget* MainGameUI;

public:
	///////////////////////////////////////////////////////////////////////////
	/// @brief Set default mouse cursor settings.
	ARandomTDPlayerController();

  ///////////////////////////////////////////////////////////////////////////
  /// @brief  Setup bind actions and axis mappings.
  virtual void SetupInputComponent() override;

  ///////////////////////////////////////////////////////////////////////////
	UMainGameUserWidget* GetUI();

  FInteractEvent OnInteractEvent;
};
