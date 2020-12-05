// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomTDTowerFactory.h"
#include "Engine/World.h"
#include "RandomTDGridBase.h"
#include "RandomTDTowerCharacter.h"
#include "RandomTD.h"

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

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerFactory::UnselectAll()
{
	for (auto& pair : ListOfActiveTowerRefs)
	{
		pair.Key->Unselect();
	}
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerFactory::Select(ARandomTDTowerCharacter* Tower)
{
	Tower->Select();
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerFactory::AddNewTowerToList(ARandomTDGridBase* Grid, ARandomTDTowerCharacter* BP_Tower)
{
#if WITH_EDITOR
	BP_Tower->SetFolderPath("Tower");
#endif
	ListOfActiveTowerRefs.Add(BP_Tower, Grid);

	// notify us when tower is removed
	BP_Tower->OnDestroyed.AddDynamic(this, &ARandomTDTowerFactory::OnSellTower);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerFactory::OnSellTower(AActor* Tower)
{
	ARandomTDGridBase* Grid = ListOfActiveTowerRefs.FindAndRemoveChecked(Cast<ARandomTDTowerCharacter>(Tower));
	Grid->SetValid();
}
