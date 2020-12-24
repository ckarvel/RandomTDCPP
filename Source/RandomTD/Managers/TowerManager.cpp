// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerManager.h"
#include "Kismet/GameplayStatics.h"

#include "RandomTD/UI/MainGameUserWidget.h"
#include "RandomTD/RandomTDPlayerController.h" // who else includes pc?
#include "RandomTD/RandomTDGameMode.h"

#include "RandomTD/RandomTDGridBase.h"
#include "RandomTD/RandomTDTowerCharacter.h"

#include "RandomTD/RandomTD.h"

///////////////////////////////////////////////////////////////////////////////////////
ATowerManager::ATowerManager()
	: bCtrlPressed(false)
{
	PrimaryActorTick.bCanEverTick = false; // no ticking
}

/////////////////////////////////////////////////////////////////////////////////////
void ATowerManager::BeginPlay()
{
	Super::BeginPlay();

	// WARNING: Do not try to call Controller from here. Safe after Init() is called
}

/////////////////////////////////////////////////////////////////////////////////////
void ATowerManager::Init(ARandomTDPlayerController* PC)
{
	MyController = PC;
	MyController->OnInteractEvent.AddUObject(this, &ATowerManager::OnUserInteract);
}

/////////////////////////////////////////////////////////////////////////////////////
void ATowerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/////////////////////////////////////////////////////////////////////////////////////
void ATowerManager::OnUserInteract(FHitResult* Hit)
{
  if (!bTowerRequested || !Hit->bBlockingHit)
	{
		UnselectTowers();
    return;
	}
	// user wants to spawn a tower at this location. Verify that:
	// 1. location is a grid
	// 2. grid is valid

	// 1
  ECollisionChannel ObjectType = Hit->Component->GetCollisionObjectType();	
	if (ObjectType != GridTraceChannel)
		return; // a tower request is active so no need to worry about unselecting towers, just exit

	// 2
  ARandomTDGridBase* Grid = Cast<ARandomTDGridBase>(Hit->GetActor());
  if (Grid->IsValid())
    SpawnTower(Grid);
}

/////////////////////////////////////////////////////////////////////////////////////
bool ATowerManager::OnCreateBasicTowerPressed()
{
	if (bTowerRequested)
		return false; // ignore request if a request is already active
	bTowerRequested = true;
	UnselectTowers();
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////
bool ATowerManager::SpawnTower(AActor* Actor)
{
	if (!bTowerRequested)
		return false;

	if (ARandomTDGridBase* Grid = Cast<ARandomTDGridBase>(Actor))
	{
		if (Grid->IsValid())
		{
			//spawn tower on grid
			ARandomTDTowerCharacter* Tower = ARandomTDGameMode::GetTowerFactory()->SpawnTower(Grid);
#if WITH_EDITOR
			Tower->SetFolderPath("Tower");
			Tower->GetController()->SetFolderPath("Controller");
#endif
			PlayerTowerMap.Add(Tower, Grid);

			// notify us when tower is removed
			Tower->OnDestroyed.AddDynamic(this, &ATowerManager::OnSellTower);
			// set this grid to occupied
			Grid->SetInvalid();
			bTowerRequested = false;
			return true;
		}
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////
void ATowerManager::OnSellTower(AActor* Tower)
{
	ARandomTDGridBase* Grid = PlayerTowerMap.FindAndRemoveChecked(Cast<ARandomTDTowerCharacter>(Tower));
	Grid->SetValid();
}

/////////////////////////////////////////////////////////////////////////////////////
void ATowerManager::UnselectTowers()
{
	for (auto tower : SelectedTowers)
	{
		tower->OnEndUserClick();
	}
	SelectedTowers.Empty();
	// turn off
	MyController->GetUI()->SetupTowerUI(nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////
void ATowerManager::OnTowerSelected(ARandomTDTowerCharacter* SelectedTower)
{

	// check if multi-select is on
	if (bCtrlPressed)
	{
		// turn off all overlays
		for (int i = 0; i < SelectedTowers.Num(); i++)
		{
			ARandomTDTowerCharacter* Tower = SelectedTowers[i];
			if (!Tower)
			{
				UE_LOG(LogRandomTD, Error, TEXT("PlayerController::OnTowerSelected Tower NULL?"));
				continue;
			}
		}

		// turn off
		MyController->GetUI()->SetupTowerUI(nullptr);
	}
	else
	{
		// unselect others
		for (int i = 0; i < SelectedTowers.Num(); i++)
		{
			ARandomTDTowerCharacter* Tower = SelectedTowers[i];
			if (!Tower)
			{
				UE_LOG(LogRandomTD, Error, TEXT("PlayerController::OnTowerSelected Tower NULL?"));
				continue;
			}
			if (Tower != SelectedTower)
				Tower->OnEndUserClick();
		}

		// tell tower it can show its overlay now
		MyController->GetUI()->SetupTowerUI(SelectedTower);
	}

	SelectedTowers.AddUnique(SelectedTower);
}