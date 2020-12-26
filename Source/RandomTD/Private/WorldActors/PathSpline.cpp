// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldActors/PathSpline.h"
#include "Components/SplineComponent.h"
#include "RandomTD/RandomTD.h"

int ARandomTDPathSpline::NumWaypoints;
TArray<FVector> ARandomTDPathSpline::ListOfWaypoints;

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDPathSpline::ARandomTDPathSpline()
{
	PrimaryActorTick.bCanEverTick = false; // no ticking
	SplinePath = CreateDefaultSubobject<USplineComponent>("SplinePath");
	RootComponent = SplinePath;
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPathSpline::BeginPlay()
{
	Super::BeginPlay();
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPathSpline::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// store all path waypoints
	NumWaypoints = SplinePath->GetNumberOfSplinePoints();
	for (int i = 0; i < NumWaypoints; i++)
	{
		FVector Location = SplinePath->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
		ListOfWaypoints.Add(Location);
		
	}
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPathSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/////////////////////////////////////////////////////////////////////////////////////
FVector ARandomTDPathSpline::GetWaypointAtIndex(int Index)
{
	if (Index >= NumWaypoints)
	{
		return ListOfWaypoints[NumWaypoints - 1]; // return last waypoint
	}
	return ListOfWaypoints[Index];
}
