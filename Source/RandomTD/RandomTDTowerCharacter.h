// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RandomTDTowerCharacter.generated.h"

/////////////////////////////////////////////////////////////////////////////////////
UCLASS()
class RANDOMTD_API ARandomTDTowerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/////////////////////////////////////////////////////////////////////////////////////
	ARandomTDTowerCharacter();

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	virtual void BeginPlay() override;

	/////////////////////////////////////////////////////////////////////////////////////
	void OnSellTower();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	class UWidgetComponent* TowerWidgetComponent; ///< UI widget component that contains
																								 ///< @ref TowerInteractWidget

	class UTowerInteractWidget* TowerWidget; ///< Base class for the UI widget that shows
																					///< the Tower interaction overlay.

public:	
	/////////////////////////////////////////////////////////////////////////////////////
	virtual void Tick(float DeltaTime) override;

	/////////////////////////////////////////////////////////////////////////////////////
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintImplementableEvent, Category = "Base")
		void Select();
	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintImplementableEvent, Category = "Base")
		void Unselect();
};
