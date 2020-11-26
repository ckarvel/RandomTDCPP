 // Fill out your copyright notice in the Description page of Project Settings.


#include "RandomTDEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RandomTDPathSpline.h"
#include "RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDEnemyCharacter::ARandomTDEnemyCharacter()
	: CurrentWaypoint(0)
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
	PathSplineRef = (ARandomTDPathSpline*)UGameplayStatics::GetActorOfClass(
		GetWorld(), ARandomTDPathSpline::StaticClass());
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
	if (!PathSplineRef)
	{
#ifdef UE_BUILD_DEBUG
		UE_LOG(LogRandomTD, Warning, TEXT("EnemyChar: PathSpline Null??"));
#endif
		return FVector(); // this shouldn't happen
	}

	return PathSplineRef->GetWaypointAtIndex(++CurrentWaypoint);
}
/////////////////////////////////////////////////////////////////////////////////////
