///////////////////////////////////////////////////////////////////////////
// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ItemMgmtComponent.h"
#include "RandomTD/RandomTD.h"

///////////////////////////////////////////////////////////////////////////
UItemMgmtComponent::UItemMgmtComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
  // You can turn these features off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

///////////////////////////////////////////////////////////////////////////
void UItemMgmtComponent::BeginPlay()
{
	Super::BeginPlay();
}

///////////////////////////////////////////////////////////////////////////
void UItemMgmtComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

///////////////////////////////////////////////////////////////////////////
void UItemMgmtComponent::SelectTool(EItemType Type)
{
  switch (Type)
  {
  case EItemType::MELON:
    break;
  case EItemType::POTATO:
    break;
  case EItemType::PUMPKIN:
    break;
  default:
#ifdef UE_BUILD_DEBUG
    UE_LOG(LogRandomTD, Error, TEXT("%d"), Type);
#endif
    break;
  }
}
