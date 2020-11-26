 // Fill out your copyright notice in the Description page of Project Settings.


#include "RandomTDEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RandomTDPathSpline.h"
#include "RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDEnemyCharacter::ARandomTDEnemyCharacter()
	: CurrentWaypointIndex(0)
{
	PrimaryActorTick.bCanEverTick = false; // no ticking
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
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
		return ARandomTDPathSpline::GetWaypointAtIndex(CurrentWaypointIndex);
	}

	// next waypoint is valid so increment index and return
	CurrentWaypointIndex = Index;
	return ARandomTDPathSpline::GetWaypointAtIndex(CurrentWaypointIndex);
}
/////////////////////////////////////////////////////////////////////////////////////
