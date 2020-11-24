// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RandomTDGameMode.generated.h"

UCLASS(minimalapi)
class ARandomTDGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	ARandomTDGameMode();

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void StartPlay() override;
};



