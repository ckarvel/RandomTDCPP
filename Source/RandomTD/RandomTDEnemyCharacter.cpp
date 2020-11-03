 // Fill out your copyright notice in the Description page of Project Settings.


#include "RandomTDEnemyCharacter.h"

// Sets default values
ARandomTDEnemyCharacter::ARandomTDEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARandomTDEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARandomTDEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARandomTDEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

