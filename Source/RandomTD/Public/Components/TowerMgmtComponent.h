// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "TowerMgmtComponent.generated.h"

/////////////////////////////////////////////////////////////////////////////////////
UENUM(BlueprintType)
enum class ETowerType : uint8
{
  BASIC   UMETA(DisplayName = "Basic Tower"),
  EXPERT  UMETA(DisplayName = "Expert Tower")
};

/////////////////////////////////////////////////////////////////////////////////////
USTRUCT(BlueprintType)
struct FTowerTypeData : public FTableRowBase
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  ETowerType EType;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  float SpawnChance; // 0.0 to 1.0

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  int SellPrice;
};

/////////////////////////////////////////////////////////////////////////////////////
USTRUCT(BlueprintType)
struct FTowerLibrary : public FTableRowBase
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  ETowerType EType;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FName TowerName;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  TSubclassOf<AActor> TowerClass;
};

///////////////////////////////////////////////////////////////////////////
UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RANDOMTD_API UTowerMgmtComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	///////////////////////////////////////////////////////////////////////////
	UTowerMgmtComponent();

protected:
	///////////////////////////////////////////////////////////////////////////
	virtual void BeginPlay() override;

public:	
	///////////////////////////////////////////////////////////////////////////
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  ///////////////////////////////////////////////////////////////////////////
  UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Tower)
  void SpawnRandomTower();
};
