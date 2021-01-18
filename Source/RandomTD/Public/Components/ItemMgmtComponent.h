///////////////////////////////////////////////////////////////////////////
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "ItemMgmtComponent.generated.h"

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

///////////////////////////////////////////////////////////////////////////
// Acts also as ToolManager 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RANDOMTD_API UItemMgmtComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	///////////////////////////////////////////////////////////////////////////
	UItemMgmtComponent();

protected:
	///////////////////////////////////////////////////////////////////////////
	virtual void BeginPlay() override;

public:	
	///////////////////////////////////////////////////////////////////////////
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  ///////////////////////////////////////////////////////////////////////////
  void SelectTool(EItemType Type);
};
