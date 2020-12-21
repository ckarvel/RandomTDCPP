// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomTDGridFactory.h"
#include "RandomTDGridBase.h"
#include "RandomTD.h"

#define GridTraceChannel ECC_GameTraceChannel1

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDGridFactory::ARandomTDGridFactory()
	: Grid_X(18)
	, Grid_Y(18)
	, GridSize(128)
{
	PrimaryActorTick.bCanEverTick = false; // no ticking
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDGridFactory::BeginPlay()
{
	Super::BeginPlay();
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDGridFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDGridFactory::SetGridValidity(ARandomTDGridBase* Grid)
{
	FHitResult Hit;
	FVector TraceStart = Grid->GetActorLocation();
	FVector TraceEnd = TraceStart - FVector(0, 0, 1500.0);
	FCollisionQueryParams Params = FCollisionQueryParams();
	Params.bTraceComplex = true;
	if (GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, GridTraceChannel, Params))
	{
		if (Hit.GetComponent()->ComponentHasTag("EnemyPath"))
		{
			// a tower cannot be placed on this grid
			Grid->SetInvalid();
		}
		else
		{
			Grid->SetValid();
		}
	}
	else // shouldn't happen...
	{
#ifdef UE_BUILD_DEBUG
		UE_LOG(LogRandomTD, Warning, TEXT("SetGridValidity::Grid object might not have spawned correctly."));
#endif
	}
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDGridFactory::SetupGridArray(TSubclassOf<ARandomTDGridBase> BP_GridBaseClass)
{
	GridBaseClass = BP_GridBaseClass;
	// static mesh is a little bit not the same size as the grids but.. its ok. + 11 on y axis would center
	// but it looks weird
	FVector OriginPoint =  FVector(GridSize / 2, GridSize / 2, 0); // To get grids centered on ground
	for (int row = 0; row < Grid_X; row++)
	{
		float x = row * GridSize - float(Grid_X * GridSize) / 2.0;
		for (int col = 0; col < Grid_Y; col++)
		{
			// find the row,column index for each box
			float y = col * GridSize - float(Grid_Y * GridSize) / 2.0;
			FVector NewLocation = OriginPoint + FVector(x, y, 0.0);

			// spawn grid and add to our list
			auto* NewGrid = (ARandomTDGridBase*)GetWorld()->SpawnActor(GridBaseClass, &NewLocation);
#if WITH_EDITOR
			NewGrid->SetFolderPath("Grid");
#endif
			SetGridValidity(NewGrid);
			GridBaseList.Add(NewGrid);
		}
	}
}
