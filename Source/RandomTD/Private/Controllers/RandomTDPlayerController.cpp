// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/RandomTDPlayerController.h"
#include "FunctionLibrary/GameStateLibrary.h"
#include "Engine/World.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "UI/Game/MainGameUserWidget.h"
#include "WorldActors/GridBase.h"
#include "Factories/GridFactory.h"
#include "Factories/TowerFactory.h"
#include "Characters/TowerCharacter.h"
#include "Managers/TDCameraManager.h"
#include "Managers/TowerManager.h"
#include "Managers/PropManager.h"
#include "Characters/PlayerCharacter.h"
#include "RandomTD/RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDPlayerController::ARandomTDPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	MyCameraManager = NewObject<UTDCameraManager>(UTDCameraManager::StaticClass());
	MyPropManager = NewObject<UPropManager>(UPropManager::StaticClass());
	MyTowerManager = NewObject<UTowerManager>(UTowerManager::StaticClass());
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Interact",
		IE_Pressed, this, &ARandomTDPlayerController::OnInteractPressed);
	//InputComponent->BindAction("Interact",
	//	IE_Released, this, &ARandomTDPlayerController::OnInteractReleased);
	
	///////////////////////////////////////////////////////////////
	// delegate requests
	FInputActionBinding Delegate("SetDestination", IE_Pressed);
	Delegate.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
		{
			if (ARandomTDPlayerCharacter* Player = Cast<ARandomTDPlayerCharacter>(GetPawn()))
			{
				Player->SetMoveToCursor(true);
			}
		});
	InputComponent->AddActionBinding(Delegate);

	///////////////////////////////////////////////////////////////
	Delegate = FInputActionBinding("SetDestination", IE_Released);
	Delegate.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
		{
			if (ARandomTDPlayerCharacter* Player = Cast<ARandomTDPlayerCharacter>(GetPawn()))
			{
				Player->SetMoveToCursor(false);
			}
		});
	InputComponent->AddActionBinding(Delegate);

	///////////////////////////////////////////////////////////////
	Delegate = FInputActionBinding("CreateBasicTower", IE_Pressed);
	Delegate.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
		{
			if (MyTowerManager->OnCreateBasicTowerPressed())
			{
				MyPropManager->SpawnMystery(); // call blueprint to spawn specific asset
			}
		});
	InputComponent->AddActionBinding(Delegate);

	MyTowerManager->SetupInputComponent(InputComponent);
	MyCameraManager->SetupInputComponent(InputComponent);

	///////////////////////////////////////////////////////////////

	// TODO: zoom in/out
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::BeginPlay()
{
	Super::BeginPlay(); // without this, begin play in derived classes wont get called.

	// ui
	GetUI()->SetupWidget();

  // pawn
  MyPawn = (ARandomTDPlayerCharacter*)GetPawn();
  if (MyPawn == nullptr)
  {
#ifdef UE_BUILD_DEBUG
    UE_LOG(LogRandomTD, Error, TEXT("[ARandomTDPlayerController] MyPawn is NULL!"));
#endif
    return;
  }

	// managers
	MyCameraManager->Init(this);
	MyPropManager->Init(this);
  MyTowerManager->Init(this);

	// bind to tower clicked. PC needs to know when towers are selected
	//TowerFactoryRef->
	//ARandomTDTowerCharacter::OnTowerClicked.BindUObject(this, &ARandomTDPlayerController::OnTowerSelected);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	MyPropManager->Update();
	MyTowerManager->Update();

	// keep updating the destination every tick while desired
	if (MyPawn->bMoveToMouseCursor)
	{
		if (MyTowerManager->IsTowerRequested())
		{
			// cancel request
			MyTowerManager->bTowerRequested = false;
			MyPropManager->DestroyProp();
		}
		MyPawn->MoveToMouseCursor();
	}

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
	//		PropManager->DestroyProp();
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

/////////////////////////////////////////////////////////////////////////////////////
UMainGameUserWidget* ARandomTDPlayerController::GetUI()
{
	return MainGameUI;
}
