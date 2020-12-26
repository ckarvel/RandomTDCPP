// Fill out your copyright notice in the Description page of Project Settings.

#include "Managers/PropManager.h"
#include "Controllers/RandomTDPlayerController.h" // who else includes pc?
#include "UI/Game/MainGameUserWidget.h"
#include "UI/Stock/PropSelectWidget.h"
#include "WorldActors/GridBase.h"
#include "RandomTD/RandomTD.h"

///////////////////////////////////////////////////////////////////////////////////////
APropManager::APropManager()
{
	PrimaryActorTick.bCanEverTick = false; // no ticking
}

/////////////////////////////////////////////////////////////////////////////////////
void APropManager::BeginPlay()
{
	Super::BeginPlay();

	// WARNING: Do not try to call Controller from here. Safe after Init() is called
}

/////////////////////////////////////////////////////////////////////////////////////
void APropManager::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}

/////////////////////////////////////////////////////////////////////////////////////
void APropManager::Init(ARandomTDPlayerController* PC)
{
	MyController = PC;
	MyController->GetUI()->GetPropUI()->OnPropSelectEvent.BindUObject(this, &APropManager::SpawnStock);
	MyController->OnInteractEvent.AddUObject(this, &APropManager::OnUserInteract);
}

/////////////////////////////////////////////////////////////////////////////////////
void APropManager::OnUserInteract(FHitResult* Hit)
{
  // if prop doesn't exist
  // or if grid was not clicked, exit
  if (!ActiveActor || !Hit->bBlockingHit)
    return;

  // we only care if a grid was interacted with
  ECollisionChannel ObjectType = Hit->Component->GetCollisionObjectType();
  if (ObjectType != GridTraceChannel)
    return;

  // if grid not valid, exit
  ARandomTDGridBase* Grid = Cast<ARandomTDGridBase>(Hit->GetActor());
  if (!Grid->IsValid())
    return;

  // if our prop is mystery, destroy
  if (ActiveActor->ActorHasTag("Mystery"))
  {
    DestroyProp();
  }
  else  // if our prop is a stock, place
  {
    ActiveActor->SetActorLocation(Grid->GetActorLocation());
    StockActors.Add(ActiveActor);
    ActiveActor = nullptr;
  }
}

/////////////////////////////////////////////////////////////////////////////////////
void APropManager::SpawnStock(int Index)
{
	ActiveActor = GetWorld()->SpawnActor<AActor>(StockClasses[Index]);
  ActiveActor->Tags.Add("Stock");
}

/////////////////////////////////////////////////////////////////////////////////////
void APropManager::SpawnMystery()
{
  ActiveActor = GetWorld()->SpawnActor<AActor>(MysteryClass);
  ActiveActor->Tags.Add("Mystery");
}

/////////////////////////////////////////////////////////////////////////////////////
void APropManager::DestroyProp()
{
  if (ActiveActor)
    ActiveActor->Destroy();
}

/////////////////////////////////////////////////////////////////////////////////////
void APropManager::MovePropToCursor()
{
	if (MyController == nullptr || ActiveActor == nullptr)
		return;

	FHitResult Hit = MyController->GetHitOnCustomObjectTypes(true, GridTraceChannel);
	// TODO: constrain cursor movement within grid so
	// prop will move even when cursor is outside the grid
	if (Hit.bBlockingHit) // TODO: if grid hit
	{
		ActiveActor->SetActorLocation(Hit.ImpactPoint);
	}
}
