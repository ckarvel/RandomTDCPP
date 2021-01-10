// Fill out your copyright notice in the Description page of Project Settings.

#include "Managers/ItemManager.h"
#include "FunctionLibrary/GameStateLibrary.h"
#include "Controllers/RandomTDPlayerController.h" // who else includes pc?
#include "UI/Game/MainGameUserWidget.h"
#include "UI/Stock/PropSelectWidget.h"
#include "WorldActors/GridBase.h"
#include "RandomTD/RandomTD.h"

///////////////////////////////////////////////////////////////////////////////////////
UItemManager::UItemManager(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
{
}

/////////////////////////////////////////////////////////////////////////////////////
void UItemManager::Update()
{
    MovePropToCursor();
}

/////////////////////////////////////////////////////////////////////////////////////
void UItemManager::Init(ARandomTDPlayerController* PC)
{
	MyController = PC;
	MyController->GetUI()->GetPropUI()->OnPropSelectEvent.BindUObject(this, &UItemManager::SpawnStock);
	MyController->OnInteractEvent.AddUObject(this, &UItemManager::OnUserInteract);
}

/////////////////////////////////////////////////////////////////////////////////////
void UItemManager::SetupInputComponent(UInputComponent* InputComponent)
{
  InputComponent->BindAction("CreateBasicTower", IE_Pressed, this, &UItemManager::SpawnMystery);
}

/////////////////////////////////////////////////////////////////////////////////////
void UItemManager::OnUserInteract(FHitResult* Hit)
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
  //if (ActiveActor->ActorHasTag("Mystery"))
  //{
  DestroyProp();
  //}
  //else  // if our prop is a stock, place
  //{
  //  ActiveActor->SetActorLocation(Grid->GetActorLocation());
  //  //StockActors.Add(ActiveActor);
  //  ActiveActor = nullptr;
  //}
}

/////////////////////////////////////////////////////////////////////////////////////
void UItemManager::SpawnStock(int Index)
{
	//ActiveActor = MyController->GetWorld()->SpawnActor<AActor>(StockClasses[Index]);
 // ActiveActor->Tags.Add("Stock");
}

/////////////////////////////////////////////////////////////////////////////////////
void UItemManager::SpawnMystery()
{
// todo: figure out how to get mystery class! we changed this manager to uobject from actor remember
  ActiveActor = MyController->GetWorld()->SpawnActor<AActor>(MysteryClass);
}

/////////////////////////////////////////////////////////////////////////////////////
void UItemManager::DestroyProp()
{
  if (ActiveActor)
    ActiveActor->Destroy();
}

/////////////////////////////////////////////////////////////////////////////////////
void UItemManager::MovePropToCursor()
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
