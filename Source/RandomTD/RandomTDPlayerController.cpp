// Copyright Epic Games, Inc. All Rights Reserved.

#include "RandomTDPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

#include "RandomTDCharacter.h"
#include "RandomTD.h"

#define GridTraceChannel ECC_GameTraceChannel1

/////////////////////////////////////////////////////////////////////////////////////
// SETUP FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////
ARandomTDPlayerController::ARandomTDPlayerController()
	: bMoveToMouseCursor(false)
	, MysteryPropHeight(-1.0)
	, CameraMovementSpeed(300.0)
	
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

	// pawn movement
	InputComponent->BindAction("SetDestination",
		IE_Pressed, this, &ARandomTDPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination",
		IE_Released, this, &ARandomTDPlayerController::OnSetDestinationReleased);

	// player abilities
	InputComponent->BindAction("CreateBasicTower",
		IE_Pressed, this, &ARandomTDPlayerController::OnCreateBasicTowerPressed);

	InputComponent->BindAction("PerformAction",
		IE_Pressed, this, &ARandomTDPlayerController::OnPerformActionPressed);
	InputComponent->BindAction("PerformAction",
		IE_Released, this, &ARandomTDPlayerController::OnPerformActionReleased);

	// camera movement
	InputComponent->BindAxis("MoveForward", this, &ARandomTDPlayerController::MoveCameraForward);
	InputComponent->BindAxis("MoveRight", this, &ARandomTDPlayerController::MoveCameraRight);
	// TODO: zoom in/out
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::BeginPlay()
{
	// get ref to our player
	PlayerRef = (ARandomTDCharacter*)GetPawn();
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDPlayerController::BeginPlay"));
#endif
	if (PlayerRef == nullptr)
	{
#ifdef UE_BUILD_DEBUG
		UE_LOG(LogRandomTD, Error, TEXT("[BeginPlay] PlayerRef is NULL!"));
#endif
		return;
	}

	// set initial camera location
	auto Location = FVector(-450, 0, 700);
	auto Rotation = FRotator(-70, -0, 0); // pitch yaw roll
	PlayerRef->GetPlayerCamera()->SetWorldLocationAndRotation(Location, Rotation);

	// get ref to towerfactory
	TowerFactoryRef = (ATowerFactory*) UGameplayStatics::GetActorOfClass(
		GetWorld(), ATowerFactory::StaticClass());

	GridFactoryRef = (AGridFactory*)UGameplayStatics::GetActorOfClass(
		GetWorld(), AGridFactory::StaticClass());
}

/////////////////////////////////////////////////////////////////////////////////////
// TICK FUNCTIONS
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

	if (MysteryPropRef)
	{
		HighlightGrid();
		MovePropToCursor();
	}
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
void ARandomTDPlayerController::HighlightGrid()
{
	FHitResult Hit = GetCursorHitResultOnGrid();
	if (Hit.bBlockingHit)
	{
#ifdef UE_BUILD_DEBUG
		UE_LOG(LogRandomTD, Log, TEXT("PlayerController::HighlightGrid"));
#endif
		GridFactoryRef->HighlightGrid((AGridBase*)Hit.GetActor());
	}
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::MovePropToCursor()
{
	if (MysteryPropRef == nullptr)
	{
#ifdef UE_BUILD_DEBUG
		UE_LOG(LogRandomTD, Error, TEXT("[MovePropToCursor] MysteryProp is NULL!"));
#endif
		return;
	}

	FHitResult Hit = GetCursorHitResultOnGrid();
	// TODO: constrain cursor movement within grid so
	// prop will move even when cursor is outside the grid
	if (Hit.bBlockingHit) // TODO: if grid hit
	{
		// take into account the prop's height
		Hit.ImpactPoint.Z += GetPropHeight();
		MysteryPropRef->SetActorLocation(Hit.ImpactPoint);
	}
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::MoveCameraForward(float AxisValue)
{
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
	// get camera position
	FVector Location = PlayerRef->GetPlayerCamera()->GetComponentLocation();
	// modify the y axis value
	Location.Y += (CameraMovementSpeed * AxisValue);
	// set camera position to modified location
	PlayerRef->GetPlayerCamera()->SetWorldLocation(Location,false,nullptr, ETeleportType::TeleportPhysics);
}

//////////////////////////////////////////
//
void ARandomTDPlayerController::OnPerformActionPressed()
{
	if (MysteryPropRef)
	{
		if (TowerFactoryRef)
		{
			FHitResult Hit = GetCursorHitResultOnGrid();
			if (Hit.bBlockingHit)
			{
#ifdef UE_BUILD_DEBUG
				UE_LOG(LogRandomTD, Log, TEXT("PlayerController::OnPerformActionPressed"));
#endif
				// this will call BP_TowerFactory
				TowerFactoryRef->SpawnTower((AGridBase*)Hit.GetActor());
			}
		}

		MysteryPropHeight = -1.0;
		MysteryPropRef->Destroy();
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// ACTION FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::OnPerformActionReleased()
{
}

/////////////////////////////////////////////////////////////////////////////////////
// SETTERS & GETTERS
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::SetMoveToCursor(bool Value)
{
	bMoveToMouseCursor = Value;
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::SetTowerInProgress(AActor* Tower)
{
	MysteryPropRef = Tower;
}
/////////////////////////////////////////////////////////////////////////////////////
bool ARandomTDPlayerController::IsTowerInProgress()
{
	return MysteryPropRef ? true : false;
}
/////////////////////////////////////////////////////////////////////////////////////
float ARandomTDPlayerController::GetPropHeight()
{
	if (MysteryPropRef && MysteryPropHeight < 0.0)
	{
		FVector Origin;
		FVector BoxExtent;
		MysteryPropRef->GetActorBounds(false, Origin, BoxExtent);
		// this is how far from center box is in x,y,z axis
		// so its actually the prop's height divided in half
		MysteryPropHeight = BoxExtent.Z;
	}
	return MysteryPropHeight;
}
/////////////////////////////////////////////////////////////////////////////////////
FHitResult ARandomTDPlayerController::GetCursorHitResultOnGrid()
{
	FHitResult Hit;
	EObjectTypeQuery ObjectType = UEngineTypes::ConvertToObjectType(GridTraceChannel);
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Push(ObjectType);
	GetHitResultUnderCursorForObjects(ObjectTypes, false, Hit);
	return Hit;
}
