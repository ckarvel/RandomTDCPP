// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
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


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

