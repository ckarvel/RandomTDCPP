// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropManager.generated.h"

/////////////////////////////////////////////////////////////////////////////////////
UCLASS()
class UPropManager : public UObject
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Base")
	TSubclassOf<AActor> MysteryClass;

  UPROPERTY(EditAnywhere, Category = "Base")
  TArray<TSubclassOf<AActor>> StockClasses;

  AActor* ActiveActor; ///< Reference is set by BP. This allows us to easily change prop asset
                       ///< for cosmetic purposes in the future.
	class ARandomTDPlayerController* MyController;

public:
	/////////////////////////////////////////////////////////////////////////////////////
	UPropManager();

	/////////////////////////////////////////////////////////////////////////////////////
	void Init(class ARandomTDPlayerController* PC);

  ///////////////////////////////////////////////////////////////////////////
  void SetupInputComponent(UInputComponent* InputComponent);

	/////////////////////////////////////////////////////////////////////////////////////
	void Update();

	///////////////////////////////////////////////////////////////////////////
	/// @brief Remove mystery prop from the world
	UFUNCTION(BlueprintCallable, Category = "Base")
	void DestroyProp();

	///////////////////////////////////////////////////////////////////////////
	/// @brief Spawn mystery prop. This is implemented in BP and called from here (C++)
	/// @see OnCreateBasicTowerPressed()
	void SpawnMystery();

	///////////////////////////////////////////////////////////////////////////
	/// @brief Navigate the mystery prop to current cursor location
	void MovePropToCursor();

	///////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Base")
	void SpawnStock(int Index);

	///////////////////////////////////////////////////////////////////////////
	void OnUserInteract(struct FHitResult* Hit);
};
