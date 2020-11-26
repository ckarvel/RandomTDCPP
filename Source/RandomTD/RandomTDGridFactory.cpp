// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomTDGridFactory.h"
#include "RandomTDGridBase.h"
#include "RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDGridFactory::ARandomTDGridFactory()
	: Grid_X(1)
	, Grid_Y(1)
	, GridSize(128)
{
	PrimaryActorTick.bCanEverTick = false; // no ticking
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDGridFactory::Constructor"));
#endif
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDGridFactory::BeginPlay()
{
	Super::BeginPlay();
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDGridFactory::BeginPlay"));
#endif
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDGridFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
			SetGridValidity(NewGrid, NewLocation);
			GridBaseList.Add(NewGrid);
		}
	}
}
