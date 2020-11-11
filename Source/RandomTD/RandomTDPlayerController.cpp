// Copyright Epic Games, Inc. All Rights Reserved.

#include "RandomTDPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

#include "RandomTDCharacter.h"
#include "RandomTD.h"

#define GridTraceChannel ECC_GameTraceChannel1
#define TowerTraceChannel ECC_GameTraceChannel2

/////////////////////////////////////////////////////////////////////////////////////
// SETUP FUNCTIONS
/////////////////////////////////////////////////////////////////////////////////////
ARandomTDPlayerController::ARandomTDPlayerController()
	: bMoveToMouseCursor(false)
	, bTowerRequested(false)
	, CameraMovementSpeed(300.0)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDPlayerController::Constructor"));
#endif
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
	Super::BeginPlay(); // without this, beginplay in derived classes wont get called.
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

	HandleSelectedObjects();

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		//Cancel other pending actions
		MoveToMouseCursor();
	}

	if (!IsTowerInProgress())
		return;

		MovePropToCursor();
}

void ARandomTDPlayerController::HandleSelectedObjects()
{
	if (!GridFactoryRef && !TowerFactoryRef)
	{
#ifdef UE_BUILD_DEBUG
		UE_LOG(LogRandomTD, Warning, TEXT("PlayerController::HandleSelectedObjects"));
		UE_LOG(LogRandomTD, Warning, TEXT("GridFactory and TowerFactory shouldn't be null..."));
#endif
		return;
	}
		
	AGridBase* Grid = GridFactoryRef->GetSelected();
	if (Grid && bTowerRequested)
	{
		TowerFactoryRef->SpawnTower(Grid);
	}

	ATowerBase* Tower = TowerFactoryRef->GetSelected();

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
	if (!IsTowerInProgress()) // just in case...
		return;

	FHitResult Hit = GetCursorHitResultOnObjectType(GridTraceChannel);
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
	if (!IsTowerInProgress()) // just in case...
		return;
	MysteryPropRef->Destroy();
}

/////////////////////////////////////////////////////////////////////////////////////
// SETTERS & GETTERS
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::SetMoveToCursor(bool Value)
{
	bMoveToMouseCursor = Value;
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::SetTowerInProgress(AActor* MysteryProp)
{
	MysteryPropRef = MysteryProp;
}

/////////////////////////////////////////////////////////////////////////////////////
bool ARandomTDPlayerController::IsTowerInProgress()
{
	if (MysteryPropRef && !MysteryPropRef->IsPendingKill())
		return true;
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////
FHitResult ARandomTDPlayerController::GetCursorHitResultOnObjectType(ECollisionChannel Channel)
{
	FHitResult Hit;
	EObjectTypeQuery ObjectType = UEngineTypes::ConvertToObjectType(Channel);
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Push(ObjectType);
	GetHitResultUnderCursorForObjects(ObjectTypes, false, Hit);
	return Hit;
}
