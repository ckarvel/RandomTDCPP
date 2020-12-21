// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropManager.generated.h"

// the generated.h file can't be included if you don't include the UCLASS and generated body
UCLASS()
class APropManager : public AActor
{
	GENERATED_BODY()

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	virtual void BeginPlay() override;

public:
	/////////////////////////////////////////////////////////////////////////////////////
	APropManager();

	/////////////////////////////////////////////////////////////////////////////////////
	void Init(class ARandomTDPlayerController* PC, TSubclassOf<AActor>& Class);

	/////////////////////////////////////////////////////////////////////////////////////
	virtual void Tick(float DeltaTime) override;

	///////////////////////////////////////////////////////////////////////////
	/// @brief Remove mystery prop from the world
	UFUNCTION(BlueprintCallable, Category = "TowerActions")
	void DestroyProp();

	///////////////////////////////////////////////////////////////////////////
	/// @brief Spawn mystery prop. This is implemented in BP and called from here (C++)
	/// @see OnCreateBasicTowerPressed()
	void SpawnMystery();

	///////////////////////////////////////////////////////////////////////////
	/// @brief Navigate the mystery prop to current cursor location
	void MovePropToCursor();

	///////////////////////////////////////////////////////////////////////////
	UPROPERTY(BlueprintReadWrite, Category = "Tower")
	class AActor* MysteryPropRef; ///< Reference is set by BP. This allows us to easily change prop asset
																		///< for cosmetic purposes in the future.

	class ARandomTDPlayerController* MyController;

	TSubclassOf<AActor> PropClass;
};
