// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FunctionLibrary/GameStateLibrary.h"
#include "PlayerStateManager.generated.h"

class UInventoryComponent;

///////////////////////////////////////////////////////////////////////////
/// @class APlayerStateManager
/// @brief Manages player state: health, inventory, score, etc.
UCLASS()
class RANDOMTD_API APlayerStateManager : public APlayerState
{
	GENERATED_BODY()
public:
  APlayerStateManager();
  
  UPROPERTY(EditAnywhere, Category = "Base")
  UInventoryComponent* InventoryManager;
};
