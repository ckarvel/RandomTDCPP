// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RandomTDTowerCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FTowerOnClickedEvent, ARandomTDTowerCharacter*);

/////////////////////////////////////////////////////////////////////////////////////
UCLASS()
class RANDOMTD_API ARandomTDTowerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/////////////////////////////////////////////////////////////////////////////////////
	ARandomTDTowerCharacter();

	/////////////////////////////////////////////////////////////////////////////////////
	void OnSellTower();

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	virtual void BeginPlay() override;

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
	UFUNCTION()
	void OnUserClicked(AActor* TouchedActor, FKey ButtonPressed);

	/////////////////////////////////////////////////////////////////////////////////////
	/// @todo PC is the only one that can know this right?
	void OnUserUnclicked();

	static FTowerOnClickedEvent OnTowerClicked;

	bool bSelected;
};
