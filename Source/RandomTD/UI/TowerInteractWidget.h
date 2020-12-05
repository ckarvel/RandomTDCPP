// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerInteractWidget.generated.h"

DECLARE_DELEGATE(FOnSell);

/////////////////////////////////////////////////////////////////////////////////////
/// @class UTowerInteractWidget
/// @brief
UCLASS()
class RANDOMTD_API UTowerInteractWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/////////////////////////////////////////////////////////////////////////////////////
	UTowerInteractWidget(const FObjectInitializer& ObjectInitializer);

	FOnSell OnSellEvent; ///< Delegate called when @ref user wants to sell tower.

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Base")
	void OnSell();
};
