// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RandomTDTowerBase.generated.h"

DECLARE_DELEGATE_OneParam(FOnUIDeleteTowerEvent, ARandomTDTowerBase*);

UCLASS()
class RANDOMTD_API ARandomTDTowerBase : public APawn
{
	GENERATED_BODY()

public:
	/////////////////////////////////////////////////////////////////////////////////////
	///@brief Sets default values
	ARandomTDTowerBase();

	void Attack();

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @see ARandomTDPlayerController::BeginPlay()
	virtual void BeginPlay() override;

public:	
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Not used.
	virtual void Tick(float DeltaTime) override;
	/////////////////////////////////////////////////////////////////////////////////////
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintImplementableEvent, Category = "Tower")
	void Select();
	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintImplementableEvent, Category = "Tower")
	void Unselect();
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief This function is called this actor's delete button is pressed.
	/// 
	/// The UI notifies us that we are to be deleted, we notify anyone listening to our
	/// delegate, UIDeleteTowerEvent which should be TowerFactory. TF is the only one that
	/// can delete us. We can't delete ourselves.
	UFUNCTION(BlueprintCallable, Category = "Tower")
	void DestroyTower();

	UPROPERTY(BlueprintReadWrite, Category = "Tower")
	bool bIsSelected;
	static FOnUIDeleteTowerEvent UIDeleteTowerEvent;

	AActor* EnemyToAttack;
};
