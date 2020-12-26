// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/RandomTDPlayerController.h"
#include "Engine/World.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Game/MainGameUserWidget.h"
#include "WorldActors/GridBase.h"
#include "Factories/GridFactory.h"
#include "Factories/TowerFactory.h"
#include "Characters/TowerCharacter.h"
#include "Managers/TowerManager.h"
#include "Managers/PropManager.h"
#include "Characters/PlayerCharacter.h"
#include "RandomTD/RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDPlayerController::ARandomTDPlayerController()
	: CameraMovementSpeed(300.0)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	// define our custom object types
	m_CustomObjectTypes.Add(UEngineTypes::ConvertToObjectType(GridTraceChannel));
	m_CustomObjectTypes.Add(UEngineTypes::ConvertToObjectType(TowerTraceChannel));

	PropManagerClass = APropManager::StaticClass();
  TowerManagerClass = ATowerManager::StaticClass();
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
			if (TowerManager->OnCreateBasicTowerPressed())
			{
				PropManager->SpawnMystery(); // call blueprint to spawn specific asset
			}
		});
	InputComponent->AddActionBinding(Delegate);

	///////////////////////////////////////////////////////////////
	Delegate = FInputActionBinding("Multi-Select", IE_Pressed);
	Delegate.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
		{
			TowerManager->SetMultiSelectMode(true);
		});
	InputComponent->AddActionBinding(Delegate);

	///////////////////////////////////////////////////////////////
	Delegate = FInputActionBinding("Multi-Select", IE_Released);
	Delegate.ActionDelegate.GetDelegateForManualSet().BindLambda([this]()
		{
			TowerManager->SetMultiSelectMode(false);
		});
	InputComponent->AddActionBinding(Delegate);

	///////////////////////////////////////////////////////////////
	InputComponent->BindAxis("MoveForward", this, &ARandomTDPlayerController::MoveCameraForward);
	InputComponent->BindAxis("MoveRight", this, &ARandomTDPlayerController::MoveCameraRight);
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
		UE_LOG(LogRandomTD, Error, TEXT("[BeginPlay] MyPawn is NULL!"));
#endif
		return;
	}

	// managers
	PlayerCamera = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass());
	PropManager = GetWorld()->SpawnActor<APropManager>(PropManagerClass);
	TowerManager = GetWorld()->SpawnActor<ATowerManager>(TowerManagerClass);
	
	TowerManager->Init(this);
	PropManager->Init(this);

#if WITH_EDITOR
	TowerManager->SetFolderPath("Manager");
	PropManager->SetFolderPath("Manager");
#endif

	// camera
	auto Location = FVector(-835.0, -10.0, 1610.0);
	auto Rotation = FRotator(-70, 0, 0); // pitch yaw roll
	PlayerCamera->SetActorLocationAndRotation(Location, Rotation);
	PlayerCamera->GetCameraComponent()->bConstrainAspectRatio = false;
	SetViewTargetWithBlend(PlayerCamera);

	// bind to tower clicked. PC needs to know when towers are selected
	//TowerFactoryRef->
	//ARandomTDTowerCharacter::OnTowerClicked.BindUObject(this, &ARandomTDPlayerController::OnTowerSelected);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (MyPawn->bMoveToMouseCursor)
	{
		if (TowerManager->IsTowerRequested())
		{
			// cancel request
			TowerManager->bTowerRequested = false;
			PropManager->DestroyProp();
		}
		MyPawn->MoveToMouseCursor();
	}

	//if (!TowerManager->IsTowerRequested())
	//	return;

	PropManager->MovePropToCursor();
}

/////////////////////////////////////////////////////////////////////////////////////
FHitResult ARandomTDPlayerController::GetHitOnCustomObjectTypes(bool UseChannel, ECollisionChannel Channel)
{
	FHitResult Hit;
	if (UseChannel)
	{
		TArray<TEnumAsByte<EObjectTypeQuery>> Objects;
		Objects.Add(UEngineTypes::ConvertToObjectType(Channel));
		GetHitResultUnderCursorForObjects(Objects, false, Hit);
	}
	else
	{
		GetHitResultUnderCursorForObjects(m_CustomObjectTypes, false, Hit);
	}
	return Hit;
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::OnInteractPressed()
{
	// find object that was clicked on
	FHitResult Hit = GetHitOnCustomObjectTypes();
	
	if (!Hit.bBlockingHit)
	{
		TowerManager->UnselectTowers();
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
void ARandomTDPlayerController::MoveCameraForward(float AxisValue)
{
	// get camera position
	FVector Location = PlayerCamera->GetActorLocation();
	// modify the x axis value
	Location.X += (CameraMovementSpeed * AxisValue);
	// set camera position to modified location
	PlayerCamera->SetActorLocation(Location, false, nullptr, ETeleportType::TeleportPhysics);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::MoveCameraRight(float AxisValue)
{
	// get camera position
	FVector Location = PlayerCamera->GetActorLocation();
	// modify the y axis value
	Location.Y += (CameraMovementSpeed * AxisValue);
	// set camera position to modified location
	PlayerCamera->SetActorLocation(Location,false,nullptr, ETeleportType::TeleportPhysics);
}

/////////////////////////////////////////////////////////////////////////////////////
UMainGameUserWidget* ARandomTDPlayerController::GetUI()
{
	return MainGameUI;
}
