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
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Character movement walk speed is set to MaxWalkSpeed in constructor. If MaxWalkSpeed
	/// is changed in instance, without this call character movement won't get updated!
	virtual void PostInitializeComponents() override;

	int CurrentWaypointIndex;

public:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void Tick(float DeltaTime) override;
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/// @brief
	FVector GetNextWaypoint();

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float MaxWalkSpeed;
};
