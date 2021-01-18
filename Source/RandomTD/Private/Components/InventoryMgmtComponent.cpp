// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryMgmtComponent.h"

///////////////////////////////////////////////////////////////////////////
UInventoryMgmtComponent::UInventoryMgmtComponent()
{
	// Add the basic/expert tower items
  FItemInventory DefaultBasicItem;
  DefaultBasicItem.EItem = EItemType::BASIC;
  DefaultBasicItem.Amount = 1; // will only ever have 1
  MyInventory.Add(DefaultBasicItem);

  FItemInventory DefaultExpertItem;
  DefaultExpertItem.EItem = EItemType::EXPERT;
  DefaultExpertItem.Amount = 1;
  MyInventory.Add(DefaultExpertItem);

  PrimaryComponentTick.bCanEverTick = true;
}

///////////////////////////////////////////////////////////////////////////
void UInventoryMgmtComponent::BeginPlay()
{
	Super::BeginPlay();
}

///////////////////////////////////////////////////////////////////////////
void UInventoryMgmtComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
