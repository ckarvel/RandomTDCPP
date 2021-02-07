// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/RandomTDPlayerController.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Characters/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "RandomTD/RandomTD.h"
#include "Engine/World.h"

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDPlayerController::ARandomTDPlayerController()
	: bMoveToMouseCursor(false)
	, CameraMovementSpeed(30.0)
	, CameraExtents(FVector(400,400,200))
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

	InputComponent->BindAxis("MoveUp", this, &ARandomTDPlayerController::MoveCameraUp);

	InputComponent->BindAxis("MoveForward", this, &ARandomTDPlayerController::MoveCameraForward);
	InputComponent->BindAxis("MoveRight", this, &ARandomTDPlayerController::MoveCameraRight);

	InputComponent->BindAction("CreateBasicTower", IE_Pressed, this, &ARandomTDPlayerController::CreateBasicTower);

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ARandomTDPlayerController::StartMoving);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ARandomTDPlayerController::StopMoving);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::BeginPlay()
{
	Super::BeginPlay(); // without this, begin play in derived classes wont get called.
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bMoveToMouseCursor)
	{
		if (ARandomTDPlayerCharacter* Char = Cast<ARandomTDPlayerCharacter>(GetCharacter()))
		{
			Char->MoveToMouseCursor();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::MoveCameraUp(float AxisValue)
{
	if (ARandomTDPlayerCharacter* Char = Cast<ARandomTDPlayerCharacter>(GetCharacter()))
	{
		// get camera position
		FVector Location = Char->GetPlayerCamera()->GetRelativeLocation();
		// modify the x axis value
		Location.Z += (CameraMovementSpeed * 2 * -AxisValue);

		// Apply constraints
		Location.Z = FGenericPlatformMath::Min(Location.Z, Char->InitialCamLocation.GetLocation().Z + CameraExtents.Z);
		Location.Z = FGenericPlatformMath::Max(Location.Z, Char->InitialCamLocation.GetLocation().Z - CameraExtents.Z);

		// set camera position to modified location
		Char->GetPlayerCamera()->SetRelativeLocation(Location, false, nullptr, ETeleportType::TeleportPhysics);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::MoveCameraForward(float AxisValue)
{
	if (ARandomTDPlayerCharacter* Char = Cast<ARandomTDPlayerCharacter>(GetCharacter()))
	{
		// get camera position
		FVector Location = Char->GetPlayerCamera()->GetRelativeLocation();
		// modify the x axis value
		Location.X += (CameraMovementSpeed * AxisValue);

		// Apply constraints
		Location.X = FGenericPlatformMath::Min(Location.X, Char->InitialCamLocation.GetLocation().X + CameraExtents.X);
		Location.X = FGenericPlatformMath::Max(Location.X, Char->InitialCamLocation.GetLocation().X - CameraExtents.X);

		// set camera position to modified location
		Char->GetPlayerCamera()->SetRelativeLocation(Location, false, nullptr, ETeleportType::TeleportPhysics);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerController::MoveCameraRight(float AxisValue)
{
	if (ARandomTDPlayerCharacter* Char = Cast<ARandomTDPlayerCharacter>(GetCharacter()))
	{
		// get camera position
		FVector Location = Char->GetPlayerCamera()->GetRelativeLocation();
		// modify the y axis value
		Location.Y += (CameraMovementSpeed * AxisValue);

		// Apply constraints
		Location.Y = FGenericPlatformMath::Min(Location.Y, Char->InitialCamLocation.GetLocation().Y + CameraExtents.Y);
		Location.Y = FGenericPlatformMath::Max(Location.Y, Char->InitialCamLocation.GetLocation().Y - CameraExtents.Y);

		// set camera position to modified location
		Char->GetPlayerCamera()->SetRelativeLocation(Location, false, nullptr, ETeleportType::TeleportPhysics);
	}
}
