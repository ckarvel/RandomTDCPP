// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RandomTDGameInstance.generated.h"

class ULevelManager;

UCLASS()
class RANDOMTD_API URandomTDGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	virtual void OnStart();

	ULevelManager* LevelManager;

public:
		virtual void Init();
	
		inline ULevelManager& GetLevelManager() const { return *LevelManager; }
};
