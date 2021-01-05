// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RandomTDGameInstance.generated.h"

class ULevelManager;
class UStockManager;

UCLASS()
class RANDOMTD_API URandomTDGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	/////////////////////////////////////////////////////////////////////////////////////
	virtual void OnStart();

	ULevelManager* LevelManager;
	UStockManager* StockManager;

public:
	/////////////////////////////////////////////////////////////////////////////////////
	virtual void Init();
	
	/////////////////////////////////////////////////////////////////////////////////////
	inline ULevelManager& GetLevelManager() const { return *LevelManager; }

	/////////////////////////////////////////////////////////////////////////////////////
	inline UStockManager& GetStockManager() const { return *StockManager; }
};
