// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridBase.h"
#include "TowerBase.h"

#include "TowerFactory.generated.h"

UCLASS()
class RANDOMTD_API ATowerFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerFactory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnTower(AGridBase* SpawnGrid);

//public:
	TMap<AGridBase*, ATowerBase*> ListOfActiveTowerRefs;
};
