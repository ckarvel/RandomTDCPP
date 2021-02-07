// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TowerMgmtComponent.h"

///////////////////////////////////////////////////////////////////////////
UTowerMgmtComponent::UTowerMgmtComponent()
{
  bWantsInitializeComponent = true;
  PrimaryComponentTick.bCanEverTick = false;
}

///////////////////////////////////////////////////////////////////////////
void UTowerMgmtComponent::BeginPlay()
{
	Super::BeginPlay();
}

///////////////////////////////////////////////////////////////////////////
void UTowerMgmtComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
