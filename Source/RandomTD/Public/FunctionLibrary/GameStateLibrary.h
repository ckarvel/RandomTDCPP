// Copyright Epic Games, Inc. All Rights Reserved.

/**
 * This kismet library is used for helper functions primarily used in the kismet compiler for AI related nodes
 * NOTE: Do not change the signatures for any of these functions as it can break the kismet compiler and/or the nodes referencing them
 */

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Game/RandomTDGameInstance.h"
#include "Managers/LevelManager.h"
#include "GameStateLibrary.generated.h"

UCLASS(meta = (ScriptName = "GameStateLibrary"))
class RANDOMTD_API UGameStateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	static int GetCurrentLevel(UGameInstance* GameInstance);

	static int GetSecondsPerLevel(UGameInstance* GameInstance);

	static int GetPreLevelSeconds(UGameInstance* GameInstance);

	/////////////////////////////////////////////////////////////////////////////////////
	template<typename UserClass>
	static void BindToLevelStart(UGameInstance* GameInstance, UserClass* Object, void (UserClass::* MyFunc)(int));

	/////////////////////////////////////////////////////////////////////////////////////
	template<typename UserClass>
	static void BindToSecondElapsed(UGameInstance* GameInstance, UserClass* Object, void (UserClass::* MyFunc)(int));

	//static int GetPrice();
	//static GetEnumList(enum);
	//static BindToDelegate();
};

/////////////////////////////////////////////////////////////////////////////////////
template<typename UserClass>
void UGameStateLibrary::BindToLevelStart(UGameInstance* GameInstance, UserClass* Object, void (UserClass::* MyFunc)(int))
{
  if (URandomTDGameInstance* GI = Cast<URandomTDGameInstance>(GameInstance))
  {
    TBaseDelegate<void, int> test;

    GI->GetLevelManager().LevelStartEvent.AddUObject(Object, MyFunc);
  }
}

/////////////////////////////////////////////////////////////////////////////////////
template<typename UserClass>
void UGameStateLibrary::BindToSecondElapsed(UGameInstance* GameInstance, UserClass* Object, void (UserClass::* MyFunc)(int))
{
  if (URandomTDGameInstance* GI = Cast<URandomTDGameInstance>(GameInstance))
  {
    TBaseDelegate<void, int> test;

    GI->GetLevelManager().LevelSecondElapsedEvent.AddUObject(Object, MyFunc);
  }
}
