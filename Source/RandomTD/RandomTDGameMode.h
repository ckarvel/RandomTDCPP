// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RandomTDGameMode.generated.h"

UCLASS(minimalapi)
class ARandomTDGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARandomTDGameMode();

	virtual void StartPlay() override;
};



