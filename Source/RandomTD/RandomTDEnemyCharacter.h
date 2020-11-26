// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RandomTDEnemyCharacter.generated.h"

UCLASS()
class RANDOMTD_API ARandomTDEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	ARandomTDEnemyCharacter();

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void BeginPlay() override;

	int CurrentWaypoint;
	class ARandomTDPathSpline* PathSplineRef;

public:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void Tick(float DeltaTime) override;
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	FVector GetNextWaypoint();
};
