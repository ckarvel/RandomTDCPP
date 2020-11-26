// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomTDPathSpline.h"
#include "Components/SplineComponent.h"
#include "RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDPathSpline::ARandomTDPathSpline()
	: NumWaypoints(0)
{
	PrimaryActorTick.bCanEverTick = false; // no ticking
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDPathSpline::Constructor"));
#endif
	SplinePath = CreateDefaultSubobject<USplineComponent>("SplinePath");
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPathSpline::BeginPlay()
{
	Super::BeginPlay();
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDPathSpline::BeginPlay"));
#endif
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