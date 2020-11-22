// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomTDGridBase.h"
#include "RandomTD.h"

#define GridTraceChannel ECC_GameTraceChannel1

ARandomTDGridBase::ARandomTDGridBase()
	: bIsValidGrid(true)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDGridBase::Constructor"));
#endif
}
/////////////////////////////////////////////////////////////////////////////////////
// Called when the game starts or when spawned
void ARandomTDGridBase::BeginPlay()
{
	Super::BeginPlay();

#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDGridBase::BeginPlay"));
#endif
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDGridBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
