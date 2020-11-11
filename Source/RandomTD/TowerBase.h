// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TowerBase.generated.h"

UCLASS()
class RANDOMTD_API ATowerBase : public APawn
{
	GENERATED_BODY()

public:
	///@brief Sets default values
	ATowerBase();

protected:
	/// @see ARandomTDPlayerController::BeginPlay()
	virtual void BeginPlay() override;

public:	
	/// @brief Not used.
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool IsSelected() { return bIsSelected;  }
	bool bIsSelected;
};
