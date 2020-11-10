// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "RandomTD.h"
#include "GridBase.h"
#include "TowerFactory.h"

#define TowerTraceChannel ECC_GameTraceChannel2

// Sets default values
ATowerFactory::ATowerFactory()
{
 	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ATowerFactory::Constructor"));
#endif
}

// Called when the game starts or when spawned
void ATowerFactory::BeginPlay()
{
	Super::BeginPlay();
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ATowerFactory::BeginPlay"));
#endif
}

// Called every frame
void ATowerFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

////////////////////////////////////////////////////////////////////////
// BLUEPRINT-CALLABLE FUNCTIONS
////////////////////////////////////////////////////////////////////////
// Provides the tower and the grid its spawned on
void ATowerFactory::AddNewTowerToList(AGridBase* Grid, ATowerBase* BP_TowerBase)
{
	ListOfActiveTowerRefs.Add(Grid, BP_TowerBase);
}

