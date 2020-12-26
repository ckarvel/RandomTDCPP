// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TowerCharacter.h"
#include "RandomTD/RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
/// define static fields
//FTowerOnClickedEvent ARandomTDTowerCharacter::OnTowerClicked;

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDTowerCharacter::ARandomTDTowerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationYaw = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	SetCanBeDamaged(false);
	GetMesh()->SetRenderCustomDepth(false);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnClicked.AddDynamic(this, &ARandomTDTowerCharacter::OnStartUserClick);
	GetMesh()->OnBeginCursorOver.AddDynamic(this, &ARandomTDTowerCharacter::OnStartUserHover);
	GetMesh()->OnEndCursorOver.AddDynamic(this, &ARandomTDTowerCharacter::OnEndUserHover);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerCharacter::OnStartUserHover(UPrimitiveComponent* Component)
{
	GetMesh()->SetRenderCustomDepth(true);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerCharacter::OnEndUserHover(UPrimitiveComponent* Component)
{
	// if not selected, unhighlight
	// todo: this may change if hover highlight is different from selection
	if(!bSelected)
		GetMesh()->SetRenderCustomDepth(false);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerCharacter::OnSellTower()
{
	Destroy();
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerCharacter::OnStartUserClick(AActor* TouchedActor, FKey ButtonPressed)
{
	bSelected = true;
	GetMesh()->SetRenderCustomDepth(true);
	OnTowerClicked.Broadcast(this);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerCharacter::OnEndUserClick()
{
	bSelected = false;
	GetMesh()->SetRenderCustomDepth(false);
}
