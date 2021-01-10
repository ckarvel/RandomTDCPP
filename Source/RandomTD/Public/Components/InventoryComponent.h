// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

 /////////////////////////////////////////////////////////////////////////////////////
UENUM(BlueprintType)
enum class EItemType : uint8
{
  MELON   UMETA(DisplayName = "Melon"),
  POTATO  UMETA(DisplayName = "Potato"),
  PUMPKIN UMETA(DisplayName = "Pumpkin"),
  BASIC   UMETA(DisplayName = "Basic"),
  EXPERT  UMETA(DisplayName = "Expert")
};
/////////////////////////////////////////////////////////////////////////////////////
USTRUCT(BlueprintType)
struct FItemLibrary : public FTableRowBase
{
  GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EItemType EItem;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName ItemName;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TAssetPtr<UTexture2D> ItemIcon;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TAssetPtr<UStaticMesh> ItemMesh;

};
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
class RANDOMTD_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  UPROPERTY(EditAnywhere, Category = "Base")
  TArray<FItemInventory> MyInventory;
};
