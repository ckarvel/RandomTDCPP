// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomTD.h"
#include "GridBase.h"

#define GridTraceChannel ECC_GameTraceChannel1

// Sets default values
AGridBase::AGridBase()
	: bIsValidGrid(true)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	// setup grid mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Plane"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Plane");
	if (SphereMeshAsset.Object)
	{
		StaticMesh->SetStaticMesh(SphereMeshAsset.Object);
	}
	FVector Scale = FVector(1.0f);
	StaticMesh->SetWorldScale3D(Scale * 1.275f);
	StaticMesh->SetVisibility(false);
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGridBase::BeginPlay()
{
	Super::BeginPlay();

#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("AGridBase::BeginPlay"));
#endif
	// setup grid dynamic material
	if (ParentMaterial)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(ParentMaterial, StaticMesh);
		StaticMesh->SetMaterial(0, DynamicMaterial);
	}
	else
	{
#ifdef UE_BUILD_DEBUG
		UE_LOG(LogRandomTD, Error, TEXT("[BeginPlay] ParentMaterial is NULL!"));
#endif
	}
}

// Called every frame
void AGridBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridBase::HighlightGrid()
{
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("AGridBase::HighlightGrid"));
#endif
	if (bIsValidGrid)
	{
		DynamicMaterial->SetVectorParameterValue("Color", ValidTileColor);
		StaticMesh->SetVisibility(true);
	}
	else
	{
		DynamicMaterial->SetVectorParameterValue("Color", InvalidTileColor);
		StaticMesh->SetVisibility(true);
	}
}

void AGridBase::TurnOffGrid()
{
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("AGridBase::TurnOffGrid on: %s"), *GetName());
#endif
	StaticMesh->SetVisibility(false);
}

