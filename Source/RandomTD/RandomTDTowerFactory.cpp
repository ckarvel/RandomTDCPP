// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomTDTowerFactory.h"
#include "Engine/World.h"
#include "RandomTD.h"
#include "RandomTDGridBase.h"

#define TowerTraceChannel ECC_GameTraceChannel2

ARandomTDTowerFactory::ARandomTDTowerFactory()
{
 	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDTowerFactory::Constructor"));
#endif

	ARandomTDTowerBase::UIDeleteTowerEvent.BindUObject(this, &ARandomTDTowerFactory::DestroyTower);
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerFactory::BeginPlay()
{
	Super::BeginPlay();
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDTowerFactory::BeginPlay"));
#endif
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
void ARandomTDTowerFactory::Select(ARandomTDTowerBase* Tower)
{
	Tower->Select();
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerFactory::DestroyTower(ARandomTDTowerBase* Tower)
{
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDTowerFactory::DestroyTower"));
#endif	
	ARandomTDGridBase * Grid = ListOfActiveTowerRefs.FindAndRemoveChecked(Tower);
	Tower->Destroy();
	Grid->SetValid();
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerFactory::AddNewTowerToList(ARandomTDGridBase* Grid, ARandomTDTowerBase* BP_TowerBase)
{
	ListOfActiveTowerRefs.Add(BP_TowerBase, Grid);
}

