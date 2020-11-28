// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RandomTDEnemyCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChange, ARandomTDEnemyCharacter*, int);
// frozen, slowed, hexed??, but importantly -> death & despawn // figure out how to do enum...
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStateChange, ARandomTDEnemyCharacter*);

UCLASS()
class RANDOMTD_API ARandomTDEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	ARandomTDEnemyCharacter();

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void Tick(float DeltaTime) override;
	
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	FVector GetNextWaypoint();

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	void TowerDamage(int Damage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float MaxWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int MaxHealth;
	
	// delegates
	static FOnHealthChange OnHealthChangeEvent;
	static FOnStateChange OnStateChangeEvent;

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void BeginPlay() override;

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Character movement walk speed is set to MaxWalkSpeed in constructor. If MaxWalkSpeed
	/// is changed in instance, without this call character movement won't get updated!
	virtual void PostInitializeComponents() override;

	UPROPERTY(BlueprintReadWrite, Category = "Enemy")
	int Health;
	
	int CurrentWaypointIndex;
	
	bool FinishedPath;
	
	// give access to variables ^ to controller v
	friend class ARandomTDEnemyController;
};
