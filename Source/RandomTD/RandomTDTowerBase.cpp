// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomTDTowerBase.h"
#include "RandomTD.h"

FOnUIDeleteTowerEvent ARandomTDTowerBase::UIDeleteTowerEvent;

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDTowerBase::ARandomTDTowerBase()
{
	PrimaryActorTick.bCanEverTick = false; // no ticking
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
