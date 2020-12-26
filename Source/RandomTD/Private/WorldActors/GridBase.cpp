// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldActors/GridBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Math/Color.h"
#include "RandomTD/RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDGridBase::ARandomTDGridBase()
	: bIsValidGrid(true)
{
	PrimaryActorTick.bCanEverTick = false; // no need for ticking

	// setup grid's collision
	auto BoxExtent = FVector(64.0, 64.0, 1.0);
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxComponent->InitBoxExtent(BoxExtent);
	BoxComponent->SetShouldUpdatePhysicsVolume(true);
	BoxComponent->SetCanEverAffectNavigation(false);
	BoxComponent->SetVisibility(true);
	BoxComponent->SetCollisionObjectType(GridTraceChannel);
	BoxComponent->CanCharacterStepUpOn = ECB_Yes;
	BoxComponent->bDynamicObstacle = false;
	BoxComponent->bHiddenInGame = false;
	RootComponent = BoxComponent;
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDGridBase::BeginPlay()
{
	Super::BeginPlay();
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDGridBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
