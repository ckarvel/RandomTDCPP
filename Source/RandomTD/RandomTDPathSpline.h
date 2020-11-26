// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomTDPathSpline.generated.h"

UCLASS()
class RANDOMTD_API ARandomTDPathSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARandomTDPathSpline();

protected:
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void BeginPlay() override;
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void PostInitializeComponents() override;

public:	
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	virtual void Tick(float DeltaTime) override;
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief
	static FVector GetWaypointAtIndex(int Index);

	UPROPERTY(EditAnywhere, Category = "Spline")
	class USplineComponent* SplinePath;
	static int NumWaypoints;
	static TArray<FVector> ListOfWaypoints;
};
