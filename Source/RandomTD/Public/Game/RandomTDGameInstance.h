// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RandomTDGameInstance.generated.h"

class ULevelManager;
class UPriceManager;

UCLASS()
class RANDOMTD_API URandomTDGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	/////////////////////////////////////////////////////////////////////////////////////
	virtual void OnStart();

	ULevelManager* LevelManager;
	UPriceManager* PriceManager;

public:
	/////////////////////////////////////////////////////////////////////////////////////
	virtual void Init();
	
	/////////////////////////////////////////////////////////////////////////////////////
	inline ULevelManager& GetLevelManager() const { return *LevelManager; }

	/////////////////////////////////////////////////////////////////////////////////////
	inline UPriceManager& GetPriceManager() const { return *PriceManager; }
};
