// Fill out your copyright notice in the Description page of Project Settings.

#include "Managers/PropManager.h"
#include "FunctionLibrary/GameStateLibrary.h"
#include "Controllers/RandomTDPlayerController.h" // who else includes pc?
#include "UI/Game/MainGameUserWidget.h"
#include "UI/Stock/PropSelectWidget.h"
#include "WorldActors/GridBase.h"
#include "RandomTD/RandomTD.h"

///////////////////////////////////////////////////////////////////////////////////////
UPropManager::UPropManager(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
{
}

/////////////////////////////////////////////////////////////////////////////////////
void UPropManager::Update()
{
  if(ActiveActor)
    MovePropToCursor();
}

/////////////////////////////////////////////////////////////////////////////////////
void UPropManager::Init(ARandomTDPlayerController* PC)
{
	MyController = PC;
	MyController->GetUI()->GetPropUI()->OnPropSelectEvent.BindUObject(this, &UPropManager::SpawnStock);
	MyController->OnInteractEvent.AddUObject(this, &UPropManager::OnUserInteract);
}

/////////////////////////////////////////////////////////////////////////////////////
void UPropManager::OnUserInteract(FHitResult* Hit)
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
    //StockActors.Add(ActiveActor);
    ActiveActor = nullptr;
  }
}

/////////////////////////////////////////////////////////////////////////////////////
void UPropManager::SpawnStock(int Index)
{
	ActiveActor = MyController->GetWorld()->SpawnActor<AActor>(StockClasses[Index]);
  ActiveActor->Tags.Add("Stock");
}

/////////////////////////////////////////////////////////////////////////////////////
void UPropManager::SpawnMystery()
{
  ActiveActor = MyController->GetWorld()->SpawnActor<AActor>(MysteryClass);
  ActiveActor->Tags.Add("Mystery");
}

/////////////////////////////////////////////////////////////////////////////////////
void UPropManager::DestroyProp()
{
  if (ActiveActor)
    ActiveActor->Destroy();
}

/////////////////////////////////////////////////////////////////////////////////////
void UPropManager::MovePropToCursor()
{
	if (MyController == nullptr || ActiveActor == nullptr)
		return;

	FHitResult Hit = UGameStateLibrary::GetHitOnCustomObjectTypes(MyController, true, GridTraceChannel);
	// TODO: constrain cursor movement within grid so
	// prop will move even when cursor is outside the grid
	if (Hit.bBlockingHit) // TODO: if grid hit
	{
		ActiveActor->SetActorLocation(Hit.ImpactPoint);
	}
}
