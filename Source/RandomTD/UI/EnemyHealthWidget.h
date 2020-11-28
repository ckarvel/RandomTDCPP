// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class RANDOMTD_API UEnemyHealthWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	UEnemyHealthWidget(const FObjectInitializer& ObjectInitializer);

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	void SetHealth(int Value) { Health = Value; }

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	void SetMaxHealth(int Value) { MaxHealth = Value; }

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	/// UI Text Bind functions
	/////////////////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Game")
	float GetHealthPercentage() const
	{
		if (MaxHealth == 0)
			return 0.0;

		float Percent = (float)Health / (float)MaxHealth;
		return Percent;
	}

	int Health;

	int MaxHealth;
};
