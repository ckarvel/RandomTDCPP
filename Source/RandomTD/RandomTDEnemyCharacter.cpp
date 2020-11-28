 // Fill out your copyright notice in the Description page of Project Settings.


#include "RandomTDEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RandomTDPathSpline.h"
#include "RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
// Define static fields
FOnHealthChange ARandomTDEnemyCharacter::OnHealthChangeEvent;
FOnStateChange ARandomTDEnemyCharacter::OnStateChangeEvent;

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDEnemyCharacter::ARandomTDEnemyCharacter()
	: CurrentWaypointIndex(0)
	, MaxWalkSpeed(300.0)
	, FinishedPath(false)
	, Health(100)
	, MaxHealth(100)
{
	PrimaryActorTick.bCanEverTick = false; // no ticking
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// configure character movement
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	
	// set health to max
	Health = MaxHealth;
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
/////////////////////////////////////////////////////////////////////////////////////
FVector ARandomTDEnemyCharacter::GetNextWaypoint()
{
	int Index = CurrentWaypointIndex;
	
	// if next waypoint is invalid, keep and return last waypoint
	if (ARandomTDPathSpline::NumWaypoints <= ++Index)
	{
		OnStateChangeEvent.Broadcast(this); // notify despawn
		FinishedPath = true;
		return ARandomTDPathSpline::GetWaypointAtIndex(CurrentWaypointIndex);
	}

	// next waypoint is valid so increment index and return
	CurrentWaypointIndex = Index;
	return ARandomTDPathSpline::GetWaypointAtIndex(CurrentWaypointIndex);
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyCharacter::TowerDamage(int Damage)
{
	// if this attack kills us, notify health (just in case..?) & state change 
	if (Damage > Health)
	{
		Health = 0;
		OnHealthChangeEvent.Broadcast(this, Health);
		OnStateChangeEvent.Broadcast(this);
		return;
	}
	
	// otherwise, subtract our health by damage taken & notify health
	Health -= Damage;
	OnHealthChangeEvent.Broadcast(this, Health);
}
/////////////////////////////////////////////////////////////////////////////////////
