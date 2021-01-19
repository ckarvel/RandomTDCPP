// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RandomTDGameInstance.generated.h"

class UItemMgmtComponent;
class ULevelMgmtComponent;
class UPriceMgmtComponent;

/////////////////////////////////////////////////////////////////////////////////////
UCLASS(Blueprintable)
class RANDOMTD_API URandomTDGameInstance : public UGameInstance
{
	GENERATED_UCLASS_BODY()
protected:
	/////////////////////////////////////////////////////////////////////////////////////
	virtual void OnStart();

	/////////////////////////////////////////////////////////////////////////////////////
	virtual void Init();

	UPROPERTY(EditAnywhere, Category = "Base")
	UItemMgmtComponent* ItemManager;

  UPROPERTY(EditAnywhere, Category = "Base")
  ULevelMgmtComponent* LevelManager;

	UPROPERTY(EditAnywhere, Category = "Base")
	UPriceMgmtComponent* PriceManager;

public:
	/////////////////////////////////////////////////////////////////////////////////////
	UItemMgmtComponent* GetItemManager();

	/////////////////////////////////////////////////////////////////////////////////////
	ULevelMgmtComponent* GetLevelManager();

	/////////////////////////////////////////////////////////////////////////////////////
	UPriceMgmtComponent* GetPriceManager();

	/////////////////////////////////////////////////////////////////////////////////////
	UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = Managers)
	TSubclassOf<UPriceMgmtComponent> PriceManagerClass;
};
