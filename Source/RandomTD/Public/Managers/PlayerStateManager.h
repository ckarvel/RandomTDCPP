// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateManager.generated.h"

class UInventoryMgmtComponent;

///////////////////////////////////////////////////////////////////////////
/// @class APlayerStateManager
/// @brief Manages player state: health, inventory, score, etc.
UCLASS(BlueprintType)
class RANDOMTD_API APlayerStateManager : public APlayerState
{
	GENERATED_BODY()
protected:
  UPROPERTY(EditAnywhere, Category = "Base")
  UInventoryMgmtComponent* InventoryManager;

public:
  ///////////////////////////////////////////////////////////////////////////
  APlayerStateManager();

  ///////////////////////////////////////////////////////////////////////////
  UInventoryMgmtComponent* GetInventoryManager();
};
