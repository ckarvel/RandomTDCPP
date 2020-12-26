// Fill out your copyright notice in the Description page of Project Settings.

#include "Factories/TowerFactory.h"
#include "Engine/World.h"
#include "WorldActors/GridBase.h"
#include "Characters/TowerCharacter.h"
#include "RandomTD/RandomTD.h"

#define TowerTraceChannel ECC_GameTraceChannel2

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDTowerFactory::ARandomTDTowerFactory()
{
	PrimaryActorTick.bCanEverTick = false; // no ticking
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerFactory::BeginPlay()
{
	Super::BeginPlay();
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
