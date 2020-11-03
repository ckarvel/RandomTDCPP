// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "RandomTD.h"
#include "GridBase.h"
#include "TowerFactory.h"

// Sets default values
ATowerFactory::ATowerFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATowerFactory::BeginPlay()
{
	Super::BeginPlay();
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ATowerFactory::BeginPlay"));
#endif
}

// Called every frame
void ATowerFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATowerFactory::SpawnTower(AGridBase* SpawnGrid)
{
	FVector Location = SpawnGrid->GetActorLocation();
	ATowerBase* NewTower = (ATowerBase*)GetWorld()->SpawnActor(ATowerBase::StaticClass(), &Location);
	ListOfActiveTowerRefs.Add(SpawnGrid, NewTower);
}

