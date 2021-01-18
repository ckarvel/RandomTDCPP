// Copyright Epic Games, Inc. All Rights Reserved.

/**
 * This kismet library is used for helper functions primarily used in the kismet compiler for AI related nodes
 * NOTE: Do not change the signatures for any of these functions as it can break the kismet compiler and/or the nodes referencing them
 */

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Game/RandomTDGameInstance.h"
#include "GameStateLibrary.generated.h"

#define GridTraceChannel ECC_GameTraceChannel1
#define TowerTraceChannel ECC_GameTraceChannel2

class UItemMgmtComponent;
class ULevelMgmtComponent;
class UPriceMgmtComponent;
class UInventoryMgmtComponent;
class APlayerController;

/////////////////////////////////////////////////////////////////////////////////////
UCLASS(meta = (ScriptName = "GameStateLibrary"))
class RANDOMTD_API UGameStateLibrary : public UBlueprintFunctionLibrary
{
public:
	GENERATED_UCLASS_BODY()

  /////////////////////////////////////////////////////////////////////////////////////
  UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Item Manager", ScriptName = "GetItemManager", Category = "Utilities|Item"))
  static UItemMgmtComponent* GetItemManager(UGameInstance* GameInstance);

  /////////////////////////////////////////////////////////////////////////////////////
  UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Level Manager", ScriptName = "GetLevelManager", Category = "Utilities|Level"))
  static ULevelMgmtComponent* GetLevelManager(UGameInstance* GameInstance);

  /////////////////////////////////////////////////////////////////////////////////////
  UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Price Manager", ScriptName = "GetPriceManager", Category = "Utilities|Price"))
  static UPriceMgmtComponent* GetPriceManager(UGameInstance* GameInstance);
  
  /////////////////////////////////////////////////////////////////////////////////////
  UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Inventory Manager", ScriptName = "GetInventoryManager", Category = "Utilities|Inventory"))
  static UInventoryMgmtComponent* GetInventoryManager(APlayerState* PC);

  /////////////////////////////////////////////////////////////////////////////////////
	static int GetSecondsPerLevel(UGameInstance* GameInstance);

  /////////////////////////////////////////////////////////////////////////////////////
	static int GetPreLevelSeconds(UGameInstance* GameInstance);

	///////////////////////////////////////////////////////////////////////////////////////
	//template<typename UserClass>
	//static void BindToLevelStart(UGameInstance* GameInstance, UserClass* Object, void (UserClass::* MyFunc)(int));

	///////////////////////////////////////////////////////////////////////////////////////
	//template<typename UserClass>
	//static void BindToSecondElapsed(UGameInstance* GameInstance, UserClass* Object, void (UserClass::* MyFunc)(int));

 // /////////////////////////////////////////////////////////////////////////////////////
 // template<typename UserClass>
 // static void BindToPriceChange(UGameInstance* GameInstance, UserClass* Object, void (UserClass::* MyFunc)(TArray<int>));

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
//template<typename UserClass>
//void UGameStateLibrary::BindToLevelStart(UGameInstance* GameInstance, UserClass* Object, void (UserClass::* MyFunc)(int))
//{
//  if (URandomTDGameInstance* GI = Cast<URandomTDGameInstance>(GameInstance))
//  {
//    GI->GetLevelManager().LevelStartEvent.AddUObject(Object, MyFunc);
//  }
//}
//
///////////////////////////////////////////////////////////////////////////////////////
//template<typename UserClass>
//void UGameStateLibrary::BindToSecondElapsed(UGameInstance* GameInstance, UserClass* Object, void (UserClass::* MyFunc)(int))
//{
//  if (URandomTDGameInstance* GI = Cast<URandomTDGameInstance>(GameInstance))
//  {
//    GI->GetLevelManager().LevelSecondElapsedEvent.AddUObject(Object, MyFunc);
//  }
//}
//
///////////////////////////////////////////////////////////////////////////////////////
//template<typename UserClass>
//void UGameStateLibrary::BindToPriceChange(UGameInstance* GameInstance, UserClass* Object, void (UserClass::* MyFunc)(TArray<int>))
//{
//  if (URandomTDGameInstance* GI = Cast<URandomTDGameInstance>(GameInstance))
//  {
//    GI->GetPriceManager().PriceChangeEvent.AddUObject(Object, MyFunc);
//  }
//}