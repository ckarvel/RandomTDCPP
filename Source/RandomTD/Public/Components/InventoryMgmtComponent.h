// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "Components/ItemMgmtComponent.h"
#include "InventoryMgmtComponent.generated.h"

/////////////////////////////////////////////////////////////////////////////////////
USTRUCT(BlueprintType)
struct FItemInventory : public FTableRowBase
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  EItemType EItem;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  uint8 Amount;
};
/////////////////////////////////////////////////////////////////////////////////////
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RANDOMTD_API UInventoryMgmtComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
  ///////////////////////////////////////////////////////////////////////////
	UInventoryMgmtComponent();

protected:
  ///////////////////////////////////////////////////////////////////////////
	virtual void BeginPlay() override;

public:	
  ///////////////////////////////////////////////////////////////////////////
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  UPROPERTY(EditAnywhere, Category = "Base")
  TArray<FItemInventory> MyInventory;
};
