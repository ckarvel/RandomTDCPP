// Fill out your copyright notice in the Description page of Project Settings.

#include "PropManager.h"
#include "RandomTD/RandomTDPlayerController.h" // who else includes pc?

#define GridTraceChannel ECC_GameTraceChannel1
#define TowerTraceChannel ECC_GameTraceChannel2

///////////////////////////////////////////////////////////////////////////////////////
APropManager::APropManager()
{
	PrimaryActorTick.bCanEverTick = false; // no ticking
}

/////////////////////////////////////////////////////////////////////////////////////
void APropManager::BeginPlay()
{
	Super::BeginPlay();
}

/////////////////////////////////////////////////////////////////////////////////////
void APropManager::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}

/////////////////////////////////////////////////////////////////////////////////////
void APropManager::Init(ARandomTDPlayerController* PC)
{
	MyController = PC;
}

/////////////////////////////////////////////////////////////////////////////////////
void APropManager::SpawnMystery()
{
  MysteryActor = GetWorld()->SpawnActor<AActor>(MysteryClass);
}

/////////////////////////////////////////////////////////////////////////////////////
void APropManager::DestroyProp()
{
  if (MysteryActor)
    MysteryActor->Destroy();
}

/////////////////////////////////////////////////////////////////////////////////////
void APropManager::MovePropToCursor()
{
	if (MyController == nullptr)
		return;

	FHitResult Hit = MyController->GetHitOnCustomObjectTypes(true, GridTraceChannel);
	// TODO: constrain cursor movement within grid so
	// prop will move even when cursor is outside the grid
	if (Hit.bBlockingHit) // TODO: if grid hit
	{
		MysteryActor->SetActorLocation(Hit.ImpactPoint);
	}
}
