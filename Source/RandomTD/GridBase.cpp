// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomTD.h"
#include "GridBase.h"

#define GridTraceChannel ECC_GameTraceChannel1

// Sets default values
AGridBase::AGridBase()
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
	UE_LOG(LogRandomTD, Log, TEXT("AGridBase::Constructor"));
#endif
}

// Called when the game starts or when spawned
void AGridBase::BeginPlay()
{
	Super::BeginPlay();

#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("AGridBase::BeginPlay"));
#endif
}

void AGridBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


