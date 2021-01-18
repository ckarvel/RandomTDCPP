// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/PlayerStateManager.h"
#include "Components/InventoryMgmtComponent.h"

///////////////////////////////////////////////////////////////////////////
APlayerStateManager::APlayerStateManager()
{
  InventoryManager = NewObject<UInventoryMgmtComponent>(UInventoryMgmtComponent::StaticClass());
}

///////////////////////////////////////////////////////////////////////////
UInventoryMgmtComponent* APlayerStateManager::GetInventoryManager()
{
  return InventoryManager;
}
