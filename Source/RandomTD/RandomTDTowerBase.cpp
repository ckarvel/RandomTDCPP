// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomTDTowerBase.h"
#include "RandomTD.h"

FOnUIDeleteTowerEvent ARandomTDTowerBase::UIDeleteTowerEvent;

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDTowerBase::ARandomTDTowerBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerBase::BeginPlay()
{
	Super::BeginPlay();
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDTowerBase::BeginPlay"));
#endif	
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerBase::DestroyTower()
{
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("ARandomTDTowerBase::DestroyTower"));
#endif	
	UIDeleteTowerEvent.Execute(this);
}
