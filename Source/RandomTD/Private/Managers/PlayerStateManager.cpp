// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/PlayerStateManager.h"
#include "Components/InventoryComponent.h"

APlayerStateManager::APlayerStateManager()
{
  InventoryManager = CreateDefaultSubobject<UInventoryComponent>("InventoryManager");
}