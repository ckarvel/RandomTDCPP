// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomTDEnemyFactory.generated.h"

UCLASS()
class RANDOMTD_API ARandomTDEnemyFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	ARandomTDEnemyFactory();

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void BeginPlay() override;

public:	
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void Tick(float DeltaTime) override;

};
