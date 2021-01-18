// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/RandomTDPlayerController.h"
#include "FunctionLibrary/GameStateLibrary.h"
#include "Engine/World.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "WorldActors/GridBase.h"
#include "Factories/GridFactory.h"
#include "Factories/TowerFactory.h"
#include "Characters/TowerCharacter.h"
#include "Managers/TDCameraManager.h"
#include "Managers/TowerManager.h"
#include "Components/InventoryMgmtComponent.h"
#include "Characters/PlayerCharacter.h"
#include "RandomTD/RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDPlayerController::ARandomTDPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Interact", IE_Pressed, this, &ARandomTDPlayerController::OnInteractPressed);
	//InputComponent->BindAction("Interact", IE_Released, this, &ARandomTDPlayerController::OnInteractReleased);
	MyCameraManager = NewObject<UTDCameraManager>(UTDCameraManager::StaticClass());
	MyTowerManager = NewObject<UTowerManager>(UTowerManager::StaticClass());
	MyTowerManager->SetupInputComponent(InputComponent);
	MyCameraManager->SetupInputComponent(InputComponent);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::BeginPlay()
{
	Super::BeginPlay(); // without this, begin play in derived classes wont get called.

  // pawn
  MyPawn = (ARandomTDPlayerCharacter*)GetPawn();
  if (MyPawn == nullptr)
  {
#ifdef UE_BUILD_DEBUG
    UE_LOG(LogRandomTD, Error, TEXT("[ARandomTDPlayerController] MyPawn is NULL!"));
#endif
    return;
  }

	MyPawn->SetupInputComponent(InputComponent);
	// managers
	MyCameraManager->Init(this);
  MyTowerManager->Init(this);

	// bind to tower clicked. PC needs to know when towers are selected
	//TowerFactoryRef->
	//ARandomTDTowerCharacter::OnTowerClicked.BindUObject(this, &ARandomTDPlayerController::OnTowerSelected);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	MyTowerManager->Update();

	// keep updating the destination every tick while desired
	//if (MyPawn->bMoveToMouseCursor)
	//{
	//	if (MyTowerManager->IsTowerRequested())
	//	{
	//		// cancel request
	//		MyTowerManager->bTowerRequested = false;
	//		MyItemManager->DestroyProp();
	//	}
	//	MyPawn->MoveToMouseCursor();
	//}

	//if (!TowerManager->IsTowerRequested())
	//	return;
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::OnInteractPressed()
{
	// find object that was clicked on
	FHitResult Hit = UGameStateLibrary::GetHitOnCustomObjectTypes(this);
	if (!Hit.bBlockingHit)
	{
		MyTowerManager->UnselectTowers();
		return;
	}

	OnInteractEvent.Broadcast(&Hit);

	//ECollisionChannel ObjectType = Hit.Component->GetCollisionObjectType();

	//// broadcast with object type...
	//switch (ObjectType)
	//{
	//case GridTraceChannel:
	//	if (TowerManager->SpawnTower(Hit.GetActor()))
	//	{
	//		// User is placing tower on a grid
	//		ItemManager->DestroyProp();
	//	}
	//	else
	//	{
	//		// User wants to stop selecting objects
	//		TowerManager->UnselectTowers();
	//	}
	//	break;
	//case TowerTraceChannel:
	//	// Tower clicks handled by Tower Actor
	//	break;
	//default:
	//	// User wants to stop selecting objects
	//	TowerManager->UnselectTowers();
	//	break;
	//}
}
