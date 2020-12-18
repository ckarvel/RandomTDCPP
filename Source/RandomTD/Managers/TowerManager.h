// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerManager.generated.h"

// not having uclass and generated body and generated header causes crash on start
UCLASS()
class ATowerManager: public AActor
{
public:
  GENERATED_BODY()

  ///////////////////////////////////////////////////////////////////////////
  void BeginPlay();

  ///////////////////////////////////////////////////////////////////////////
  void UnselectTowers();

  ///////////////////////////////////////////////////////////////////////////
  /// @brief Called when the player presses "Q" to create a basic tower.
  /// 
  /// This will spawn the mystery prop under the cursor
  bool OnCreateBasicTowerPressed();
  
  ///////////////////////////////////////////////////////////////////////////
  void OnTowerSelected(class ARandomTDTowerCharacter* SelectedTower);

  ///////////////////////////////////////////////////////////////////////////
  /// @brief Removes tower from our list and validates the associated grid
  UFUNCTION()
  void OnSellTower(AActor* Tower);

  ///////////////////////////////////////////////////////////////////////////
  bool SpawnTower(AActor* Actor);

  ///////////////////////////////////////////////////////////////////////////
  void SetMultiSelectMode(bool Value) { bCtrlPressed = Value; }

  ///////////////////////////////////////////////////////////////////////////
  void Init(class ARandomTDPlayerController* Ref);

  ///////////////////////////////////////////////////////////////////////////
  bool IsTowerRequested() const { return bTowerRequested; }

  ///////////////////////////////////////////////////////////////////////////
  bool bCtrlPressed;  ///< User pressed Ctrl (Multi-select)
  bool bTowerRequested; ///< User pressed Q
  TArray<class ARandomTDTowerCharacter*> SelectedTowers;
  TMap<class ARandomTDTowerCharacter*, class ARandomTDGridBase*> PlayerTowerMap; ///< List of tower actors in the world.
private:
  // dunno how to make this const; cannot pass constructor args...
  class ARandomTDPlayerController* MyControllerRef;
  class ARandomTDTowerFactory* TowerFactoryRef;
};
