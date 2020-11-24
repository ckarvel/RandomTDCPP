// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomTDGameMode.h"
#include "RandomTDPlayerController.h"
#include "RandomTDPlayerCharacter.h"
#include "RandomTD.h"
#include "Camera/CameraActor.h"
#include "UObject/ConstructorHelpers.h"

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDGameMode::ARandomTDGameMode()
{
	PlayerControllerClass = ARandomTDPlayerController::StaticClass();

#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDGameMode::Constructor"));
#endif
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDGameMode::StartPlay()
{
	Super::StartPlay();
}