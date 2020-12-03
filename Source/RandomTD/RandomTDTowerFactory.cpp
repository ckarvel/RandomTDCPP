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
//#ifdef UE_BUILD_DEBUG
//	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDTowerFactory::Constructor"));
//#endif
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerFactory::BeginPlay()
{
	Super::BeginPlay();
//#ifdef UE_BUILD_DEBUG
//	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDTowerFactory::BeginPlay"));
//#endif

	// delegate binding should happen here not in constructor!
	//ARandomTDTowerCharacter::UIDeleteTowerEvent.BindUObject(this, &ARandomTDTowerFactory::DestroyTower);
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
void ARandomTDTowerFactory::DestroyTower(ARandomTDTowerCharacter* Tower)
{
//#ifdef UE_BUILD_DEBUG
//	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDTowerFactory::DestroyTower"));
//#endif	
	ARandomTDGridBase * Grid = ListOfActiveTowerRefs.FindAndRemoveChecked(Tower);
	Tower->Destroy();
	Grid->SetValid();
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerFactory::AddNewTowerToList(ARandomTDGridBase* Grid, ARandomTDTowerCharacter* BP_Tower)
{
	//BP_Tower->OnDestroyed()
	ListOfActiveTowerRefs.Add(BP_Tower, Grid);
}

