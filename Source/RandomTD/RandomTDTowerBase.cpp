// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomTDTowerBase.h"
#include "Kismet/GameplayStatics.h"
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
	UIDeleteTowerEvent.Execute(this);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerBase::Attack()
{
	UGameplayStatics::ApplyDamage(EnemyToAttack, 5.0, NULL, NULL, NULL);
}

//static float ApplyDamage(AActor* DamagedActor, float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<class UDamageType> DamageTypeClass);
