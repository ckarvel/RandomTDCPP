// Copyright Epic Games, Inc. All Rights Reserved.

#include "RandomTDPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

#include "RandomTDCharacter.h"
#include "RandomTD.h"

#define GridTraceChannel ECC_GameTraceChannel1

ARandomTDPlayerController::ARandomTDPlayerController()
	: CameraMovementSpeed(300.0)
	, MysteryPropHalfHeight(-1.0)
	, bPropActive(false)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

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

void ARandomTDPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		//Cancel other pending actions
		MoveToMouseCursor();
	}

	if (MysteryPropRef && bPropActive)
	{
		HighlightGrid();
		MovePropToCursor();
	}
}

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
	//InputComponent->BindAxis("MoveRight", this, &ARandomTDPlayerController::MoveCameraRight);
}

void ARandomTDPlayerController::HighlightGrid()
{
	FHitResult Hit;
	EObjectTypeQuery ObjectType = UEngineTypes::ConvertToObjectType(GridTraceChannel);
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Push(ObjectType);
	GetHitResultUnderCursorForObjects(ObjectTypes, false, Hit);

	if (Hit.bBlockingHit)
	{
#ifdef UE_BUILD_DEBUG
		UE_LOG(LogRandomTD, Log, TEXT("PlayerController::HighlightGrid"));
#endif
		GridFactoryRef->HighlightGrid(Hit.GetActor());
	}
}

void ARandomTDPlayerController::MovePropToCursor()
{
	if (MysteryPropRef == nullptr)
	{
#ifdef UE_BUILD_DEBUG
		UE_LOG(LogRandomTD, Error, TEXT("[MovePropToCursor] MysteryProp is NULL!"));
#endif
		return;
	}
	else if (MysteryPropHalfHeight < 0.0)
	{
		FVector Origin;
		FVector BoxExtent; // how far from center box is in x,y,z axis
		MysteryPropRef->GetActorBounds(false, Origin, BoxExtent);
		MysteryPropHalfHeight = BoxExtent.Z;
	}

	bPropActive = true;

	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	EObjectTypeQuery ObjectType = UEngineTypes::ConvertToObjectType(GridTraceChannel);
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Push(ObjectType);
	GetHitResultUnderCursorForObjects(ObjectTypes, false, Hit);

	// TODO: constrain cursor movement within grid so
	// prop will move even when cursor is outside the grid
	if (Hit.bBlockingHit) // TODO: if grid hit
	{
		// take into account the prop's height
		Hit.ImpactPoint.Z += MysteryPropHalfHeight;
		MysteryPropRef->SetActorLocation(Hit.ImpactPoint);
	}
}

void ARandomTDPlayerController::OnPerformActionPressed()
{
	if (MysteryPropRef)
	{
		if (TowerFactoryRef)
		{
			//TowerFactoryRef->SpawnTower();
		}

		//MysteryPropRef->
		bPropActive = false;
	}
}

void ARandomTDPlayerController::OnPerformActionReleased()
{

}

void ARandomTDPlayerController::OnCreateBasicTowerPressed()
{
	// avoid repeatedly creating mystery box if one is already active
	if (MysteryPropRef != nullptr)
		return;
	// spawn new mystery prop
	MysteryPropRef = GetWorld()->SpawnActor(MysteryPropClass);
	MovePropToCursor();
	bPropActive = true;
}

void ARandomTDPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ARandomTDPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

// called every tick
void ARandomTDPlayerController::MoveCameraForward(float AxisValue)
{
	// get camera position
	FVector Location = PlayerRef->GetPlayerCamera()->GetComponentLocation();
	// modify the x axis value
	Location.X += (CameraMovementSpeed * AxisValue);
	// set camera position to modified location
	PlayerRef->GetPlayerCamera()->SetWorldLocation(Location, false, nullptr, ETeleportType::TeleportPhysics);
}

// called every tick
void ARandomTDPlayerController::MoveCameraRight(float AxisValue)
{
	// get camera position
	FVector Location = PlayerRef->GetPlayerCamera()->GetComponentLocation();
	// modify the y axis value
	Location.Y += (CameraMovementSpeed * AxisValue);
	// set camera position to modified location
	PlayerRef->GetPlayerCamera()->SetWorldLocation(Location,false,nullptr, ETeleportType::TeleportPhysics);
}

void ARandomTDPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void ARandomTDPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	if (PlayerRef)
	{
		float const Distance = FVector::Dist(DestLocation, PlayerRef->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}


