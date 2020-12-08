// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomTDPlayerController.h"
#include "Engine/World.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MainGameUserWidget.h"
#include "RandomTDGridBase.h"
#include "RandomTDGridFactory.h"
#include "RandomTDTowerFactory.h"
#include "RandomTDTowerCharacter.h"
#include "RandomTDPlayerCharacter.h"
#include "RandomTD.h"

#define GridTraceChannel ECC_GameTraceChannel1
#define TowerTraceChannel ECC_GameTraceChannel2

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDPlayerController::ARandomTDPlayerController()
	: bMoveToMouseCursor(false)
	, bTowerRequested(false)
	, bCtrlPressed(false)
	, CameraMovementSpeed(300.0)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	// define our custom object types
	m_CustomObjectTypes.Add(UEngineTypes::ConvertToObjectType(GridTraceChannel));
	m_CustomObjectTypes.Add(UEngineTypes::ConvertToObjectType(TowerTraceChannel));
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// pawn movement
	InputComponent->BindAction("SetDestination",
		IE_Pressed, this, &ARandomTDPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination",
		IE_Released, this, &ARandomTDPlayerController::OnSetDestinationReleased);

	// player abilities
	InputComponent->BindAction("CreateBasicTower",
		IE_Pressed, this, &ARandomTDPlayerController::OnCreateBasicTowerPressed);

	InputComponent->BindAction("Interact",
		IE_Pressed, this, &ARandomTDPlayerController::OnInteractPressed);
	InputComponent->BindAction("Interact",
		IE_Released, this, &ARandomTDPlayerController::OnInteractReleased);

	InputComponent->BindAction("Multi-Select",
		IE_Pressed, this, &ARandomTDPlayerController::OnMultiSelectPressed);
	InputComponent->BindAction("Multi-Select",
		IE_Released, this, &ARandomTDPlayerController::OnMultiSelectReleased);

	// camera movement
	InputComponent->BindAxis("MoveForward", this, &ARandomTDPlayerController::MoveCameraForward);
	InputComponent->BindAxis("MoveRight", this, &ARandomTDPlayerController::MoveCameraRight);
	// TODO: zoom in/out
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::BeginPlay()
{
	Super::BeginPlay(); // without this, beginplay in derived classes wont get called.

	// get ref to our player
	PlayerRef = (ARandomTDPlayerCharacter*)GetPawn();
	if (PlayerRef == nullptr)
	{
#ifdef UE_BUILD_DEBUG
		UE_LOG(LogRandomTD, Error, TEXT("[BeginPlay] PlayerRef is NULL!"));
#endif
		return;
	}

	// set initial camera location
	auto Location = FVector(-835.0, -10.0, 1610.0);
	auto Rotation = FRotator(-70, 0, 0); // pitch yaw roll
	PlayerRef->GetPlayerCamera()->SetWorldLocationAndRotation(Location, Rotation);

	// get reference to factories
	TowerFactoryRef = (ARandomTDTowerFactory*) UGameplayStatics::GetActorOfClass(
		GetWorld(), ARandomTDTowerFactory::StaticClass());
	GridFactoryRef = (ARandomTDGridFactory*)UGameplayStatics::GetActorOfClass(
		GetWorld(), ARandomTDGridFactory::StaticClass());

	// bind to tower clicked. PC needs to know when towers are selected
	ARandomTDTowerCharacter::OnTowerClicked.BindUObject(this, &ARandomTDPlayerController::OnTowerSelected);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::OnTowerSelected(ARandomTDTowerCharacter* SelectedTower)
{
	// check if multi-select is on
	if (bCtrlPressed)
	{
		// turn off all overlays
		for (int i = 0; i < TowersSelectedList.Num(); i++)
		{
			ARandomTDTowerCharacter* Tower = TowersSelectedList[i];
			if (!Tower)
			{
				UE_LOG(LogRandomTD, Error, TEXT("PlayerController::OnTowerSelected Tower NULL?"));
				continue;
			}
		}

		// turn off
		MainGameUI->SetupTowerUI(nullptr);
	}
	else
	{
		// unselect others
		for (int i = 0; i < TowersSelectedList.Num(); i++)
		{
			ARandomTDTowerCharacter* Tower = TowersSelectedList[i];
			if (!Tower)
			{
				UE_LOG(LogRandomTD, Error, TEXT("PlayerController::OnTowerSelected Tower NULL?"));
				continue;
			}
			Tower->OnUserUnclicked();
		}
		
		// tell tower it can show its overlay now
		MainGameUI->SetupTowerUI(SelectedTower);
	}

	TowersSelectedList.AddUnique(SelectedTower);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		//Cancel other pending actions
		MoveToMouseCursor();
	}

	if (!bTowerRequested)
		return;

		MovePropToCursor();
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
		//TowerFactoryRef->UnselectAll();
		return;
	}
	ECollisionChannel ObjectType = Hit.Component->GetCollisionObjectType();
	switch (ObjectType)
	{
	case GridTraceChannel:
		// Grid clicked on:
		if (bTowerRequested)
		{
			ARandomTDGridBase* Grid = (ARandomTDGridBase*)Hit.GetActor();
			if (Grid->IsValid())
			{
				TowerFactoryRef->SpawnTower(Grid);
				Grid->SetInvalid();
				bTowerRequested = false;
				DestroyProp();
			}
		}
		else
		{
			//TowerFactoryRef->UnselectAll();
		}
		break;
	default:
		// If something other than Tower or Grid was clicked on:
		//TowerFactoryRef->UnselectAll();
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::OnCreateBasicTowerPressed()
{
	if (bTowerRequested)
		return; // ignore request if a request is already active
	bTowerRequested = true;
	SpawnMystery(); // call blueprint to spawn specific asset
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::OnMultiSelectPressed()
{
	bCtrlPressed = true;
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::OnMultiSelectReleased()
{
	bCtrlPressed = false;
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (PlayerRef && Hit.bBlockingHit)
	{
		// We hit something, move there
		FVector DestLocation = Hit.ImpactPoint;
		float const Distance = FVector::Dist(DestLocation, PlayerRef->GetActorLocation());
		// We need to issue move command only if far enough
		// in order for walk animation to play correctly
		if (Distance > 120.0f)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::MovePropToCursor()
{
	FHitResult Hit = GetHitOnCustomObjectTypes(true, GridTraceChannel);
	// TODO: constrain cursor movement within grid so
	// prop will move even when cursor is outside the grid
	if (Hit.bBlockingHit) // TODO: if grid hit
	{
		MysteryPropRef->SetActorLocation(Hit.ImpactPoint);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::MoveCameraForward(float AxisValue)
{
	if (!PlayerRef)
	{
#ifdef UE_BUILD_DEBUG
		UE_LOG(LogRandomTD, Error, TEXT("PlayerController::MoveCameraForward PlayerRef NULL?"));
#endif
		return;
	}
	// get camera position
	FVector Location = PlayerRef->GetPlayerCamera()->GetComponentLocation();
	// modify the x axis value
	Location.X += (CameraMovementSpeed * AxisValue);
	// set camera position to modified location
	PlayerRef->GetPlayerCamera()->SetWorldLocation(Location, false, nullptr, ETeleportType::TeleportPhysics);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::MoveCameraRight(float AxisValue)
{
	if (!PlayerRef)
	{
#ifdef UE_BUILD_DEBUG
		UE_LOG(LogRandomTD, Error, TEXT("PlayerController::MoveCameraForward PlayerRef NULL?"));
#endif
		return;
	}
	// get camera position
	FVector Location = PlayerRef->GetPlayerCamera()->GetComponentLocation();
	// modify the y axis value
	Location.Y += (CameraMovementSpeed * AxisValue);
	// set camera position to modified location
	PlayerRef->GetPlayerCamera()->SetWorldLocation(Location,false,nullptr, ETeleportType::TeleportPhysics);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::DestroyProp()
{
	MysteryPropRef->Destroy();
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::SetMoveToCursor(bool Value)
{
	bMoveToMouseCursor = Value;
}
