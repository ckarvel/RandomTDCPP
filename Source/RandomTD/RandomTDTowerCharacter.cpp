// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomTDTowerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/TowerInteractWidget.h"
#include "RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
/// define static fields
FTowerOnClickedEvent ARandomTDTowerCharacter::OnTowerClicked;

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDTowerCharacter::ARandomTDTowerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SetCanBeDamaged(false);
	GetMesh()->SetRenderCustomDepth(false);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnClicked.AddDynamic(this, &ARandomTDTowerCharacter::OnUserClicked);
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
void ARandomTDTowerCharacter::OnSellTower()
{
	Destroy();
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerCharacter::OnUserClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	bSelected = true; // why?
	GetMesh()->SetRenderCustomDepth(true);
	OnTowerClicked.ExecuteIfBound(this);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerCharacter::OnUserUnclicked()
{
	bSelected = false; // why?
	GetMesh()->SetRenderCustomDepth(false);
}
