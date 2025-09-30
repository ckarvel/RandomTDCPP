// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AIController.h"
#include "PerceptionFunctionLibrary.generated.h"
/**
 * 
 */
UCLASS()
class RANDOMTD_API UPerceptionFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static bool SetSightRange(AAIController* Controller, UAIPerceptionComponent* PerceptionComponent, float NewSightRange, float NewLoseSightRange);
};
