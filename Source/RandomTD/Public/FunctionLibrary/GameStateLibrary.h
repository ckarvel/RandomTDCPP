// Copyright Epic Games, Inc. All Rights Reserved.

/**
 * This kismet library is used for helper functions primarily used in the kismet compiler for AI related nodes
 * NOTE: Do not change the signatures for any of these functions as it can break the kismet compiler and/or the nodes referencing them
 */

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "Game/RandomTDGameInstance.h"
#include "Managers/LevelManager.h"
#include "Managers/StockManager.h"
#include "GameStateLibrary.generated.h"

#define GridTraceChannel ECC_GameTraceChannel1
#define TowerTraceChannel ECC_GameTraceChannel2

UENUM(BlueprintType)
enum class EItemType : uint8
{
  MELON   UMETA(DisplayName = "Melon"),
  POTATO  UMETA(DisplayName = "Potato"),
  PUMPKIN UMETA(DisplayName = "Pumpkin"),
  BASIC   UMETA(DisplayName = "Basic"),
  EXPERT  UMETA(DisplayName = "Expert")
};

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

USTRUCT(BlueprintType)
struct FItemInventory : public FTableRowBase
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  EItemType EItem;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  uint8 Amount;
};

UCLASS(meta = (ScriptName = "GameStateLibrary"))
class RANDOMTD_API UGameStateLibrary : public UBlueprintFunctionLibrary
{
public:
	GENERATED_UCLASS_BODY()
  /////////////////////////////////////////////////////////////////////////////////////
	static int GetCurrentLevel(UGameInstance* GameInstance);

  /////////////////////////////////////////////////////////////////////////////////////
	static int GetSecondsPerLevel(UGameInstance* GameInstance);

  /////////////////////////////////////////////////////////////////////////////////////
	static int GetPreLevelSeconds(UGameInstance* GameInstance);

	/////////////////////////////////////////////////////////////////////////////////////
	template<typename UserClass>
	static void BindToLevelStart(UGameInstance* GameInstance, UserClass* Object, void (UserClass::* MyFunc)(int));

	/////////////////////////////////////////////////////////////////////////////////////
	template<typename UserClass>
	static void BindToSecondElapsed(UGameInstance* GameInstance, UserClass* Object, void (UserClass::* MyFunc)(int));

  /////////////////////////////////////////////////////////////////////////////////////
  template<typename UserClass>
  static void BindToPriceChange(UGameInstance* GameInstance, UserClass* Object, void (UserClass::* MyFunc)(TArray<int>));

  ///////////////////////////////////////////////////////////////////////////
  /// @brief Gets Mouse cursor hit on custom object types, Grid and Tower
  /// @param UseChannel If True, Only get the Mouse cursor hit on object type of Channel
  /// @param Channel Object type to get hit result on
  /// @return Hit Result from cursor
  static FHitResult GetHitOnCustomObjectTypes(APlayerController* PC, bool UseChannel = false, ECollisionChannel Channel = ECC_WorldStatic);

	//static int GetPrice();
	//static GetEnumList(enum);
};

/////////////////////////////////////////////////////////////////////////////////////
template<typename UserClass>
void UGameStateLibrary::BindToLevelStart(UGameInstance* GameInstance, UserClass* Object, void (UserClass::* MyFunc)(int))
{
  if (URandomTDGameInstance* GI = Cast<URandomTDGameInstance>(GameInstance))
  {
    GI->GetLevelManager().LevelStartEvent.AddUObject(Object, MyFunc);
  }
}

/////////////////////////////////////////////////////////////////////////////////////
template<typename UserClass>
void UGameStateLibrary::BindToSecondElapsed(UGameInstance* GameInstance, UserClass* Object, void (UserClass::* MyFunc)(int))
{
  if (URandomTDGameInstance* GI = Cast<URandomTDGameInstance>(GameInstance))
  {
    GI->GetLevelManager().LevelSecondElapsedEvent.AddUObject(Object, MyFunc);
  }
}

/////////////////////////////////////////////////////////////////////////////////////
template<typename UserClass>
void UGameStateLibrary::BindToPriceChange(UGameInstance* GameInstance, UserClass* Object, void (UserClass::* MyFunc)(TArray<int>))
{
  if (URandomTDGameInstance* GI = Cast<URandomTDGameInstance>(GameInstance))
  {
    GI->GetStockManager().PriceChangeEvent.AddUObject(Object, MyFunc);
  }
}