// Copyright Epic Games, Inc. All Rights Reserved.

#include "RandomTDGameMode.h"
#include "RandomTDPlayerController.h"
#include "RandomTDCharacter.h"
#include "RandomTD.h"
#include "Camera/CameraActor.h"
#include "UObject/ConstructorHelpers.h"

ARandomTDGameMode::ARandomTDGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARandomTDPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDGameMode::Constructor"));
#endif
}

void ARandomTDGameMode::StartPlay()
{
	Super::StartPlay();
}