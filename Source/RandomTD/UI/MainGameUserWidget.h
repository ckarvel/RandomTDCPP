// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Internationalization/Internationalization.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "TowerInteractWidget.h"
#include "RoundInfoWidget.h"
#include "MainGameUserWidget.generated.h"

/////////////////////////////////////////////////////////////////////////////////////
/// @remark Delegate binding happens in constructor. This can cause a crash if UI is
/// constructed before dependencies.
UCLASS()
class RANDOMTD_API UMainGameUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	UMainGameUserWidget(const FObjectInitializer& ObjectInitializer);

	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Base")
	bool GetTowerUIVisibility() { return TowerVisibility; }

	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintImplementableEvent, Category = "Base")
	void SetTowerReference(class ARandomTDTowerCharacter* TowerActor);

	/////////////////////////////////////////////////////////////////////////////////////
	void SetupTowerUI(class ARandomTDTowerCharacter* TowerActor);

	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintImplementableEvent, Category = "Base")
	void SetupWidget();

	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintImplementableEvent, Category = "Base")
	class UPropSelectWidget* GetPropUI();

	bool TowerVisibility;
};
