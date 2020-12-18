// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerManager.h"
#include "Kismet/GameplayStatics.h"

#include "RandomTD/UI/MainGameUserWidget.h"
#include "RandomTD/RandomTDPlayerController.h" // who else includes pc?
#include "RandomTD/RandomTDGameMode.h"

#include "RandomTD/RandomTDGridBase.h"
#include "RandomTD/RandomTDTowerCharacter.h"

#include "RandomTD/RandomTD.h"

///////////////////////////////////////////////////////////////////////////
void ATowerManager::Init(ARandomTDPlayerController* Ref)
{
	MyControllerRef = Ref; // should be const ptr.. this class only reads
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
void ATowerManager::BeginPlay()
{
	bCtrlPressed = false;
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
		tower->OnUserUnclicked();
	}
	SelectedTowers.Empty();
	// turn off
	MyControllerRef->GetUI()->SetupTowerUI(nullptr);
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
		MyControllerRef->GetUI()->SetupTowerUI(nullptr);
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
				Tower->OnUserUnclicked();
		}

		// tell tower it can show its overlay now
		MyControllerRef->GetUI()->SetupTowerUI(SelectedTower);
	}

	SelectedTowers.AddUnique(SelectedTower);
}