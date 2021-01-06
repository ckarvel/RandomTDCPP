// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/TDCameraManager.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Controllers/RandomTDPlayerController.h"

/////////////////////////////////////////////////////////////////////////////////////
UTDCameraManager::UTDCameraManager(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
  , CameraMovementSpeed(300.0)
{
}

/////////////////////////////////////////////////////////////////////////////////////
void UTDCameraManager::Init(ARandomTDPlayerController* PC)
{
  MyController = PC;

  PlayerCamera = MyController->GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass());
  auto Location = FVector(-835.0, -10.0, 1610.0);
  auto Rotation = FRotator(-70, 0, 0); // pitch yaw roll
  PlayerCamera->SetActorLocationAndRotation(Location, Rotation);
  PlayerCamera->GetCameraComponent()->bConstrainAspectRatio = false;

  MyController->SetViewTargetWithBlend(PlayerCamera);
}

/////////////////////////////////////////////////////////////////////////////////////
void UTDCameraManager::SetupInputComponent(UInputComponent* InputComponent)
{
  InputComponent->BindAxis("MoveForward", this, &UTDCameraManager::MoveCameraForward);
  InputComponent->BindAxis("MoveRight", this, &UTDCameraManager::MoveCameraRight);
  // todo zoom
}

/////////////////////////////////////////////////////////////////////////////////////
void UTDCameraManager::MoveCameraForward(float AxisValue)
{
  // get camera position
  FVector Location = PlayerCamera->GetActorLocation();
  // modify the x axis value
  Location.X += (CameraMovementSpeed * AxisValue);
  // set camera position to modified location
  PlayerCamera->SetActorLocation(Location, false, nullptr, ETeleportType::TeleportPhysics);
}

/////////////////////////////////////////////////////////////////////////////////////
void UTDCameraManager::MoveCameraRight(float AxisValue)
{
  // get camera position
  FVector Location = PlayerCamera->GetActorLocation();
  // modify the y axis value
  Location.Y += (CameraMovementSpeed * AxisValue);
  // set camera position to modified location
  PlayerCamera->SetActorLocation(Location, false, nullptr, ETeleportType::TeleportPhysics);
}