// Fill out your copyright notice in the Description page of Project Settings.


#include "GridFactory.h"
#include "RandomTD.h"

// Sets default values
AGridFactory::AGridFactory()
	: Grid_X(1)
	, Grid_Y(1)
	, GridSize(128)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGridFactory::BeginPlay()
{
	Super::BeginPlay();
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("AGridFactory::BeginPlay"));
#endif
}

// Called by BP_GridFactory
void AGridFactory::SetupGridArray(TSubclassOf<AGridBase> BP)
{
	GridBaseClass = BP;
	// our starting point is this actor's location (GridFactory)
	FVector OriginPoint = GetActorLocation();
	for (int row = 0; row < Grid_X; row++)
	{
		float x = row * GridSize - float(Grid_X * GridSize) / 2.0; // centered around origin
		for (int col = 0; col < Grid_Y; col++)
		{
			// find the row,column index for each box
			float y = col * GridSize - float(Grid_Y * GridSize) / 2.0;
			FVector NewLocation = OriginPoint + FVector(x, y, 0.0); // centered around origin

			// spawn grid and add to our list
			auto* NewGrid = (AGridBase*)GetWorld()->SpawnActor(GridBaseClass, &NewLocation);
			GridBaseList.Add(NewGrid);
		}
	}
}

// Called every frame
void AGridFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridFactory::HighlightGrid(AActor* Grid)
{
	UE_LOG(LogRandomTD, Log, TEXT("%s"), *Grid->GetName())
#ifdef UE_BUILD_DEBUG
		UE_LOG(LogRandomTD, Log, TEXT("AGridFactory::HighlightGrid"));
#endif
	if (LastTarget)
	{
		LastTarget->TurnOffGrid();
	}
	LastTarget = (AGridBase*)Grid;
	LastTarget->HighlightGrid();
}