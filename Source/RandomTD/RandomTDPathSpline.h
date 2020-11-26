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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Path)
	TArray<FVector> ListOfWaypoints;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetWaypointAtIndex(int Index);

	/////////////////////////////////////////////////////////////////////////////////////
	UPROPERTY(EditAnywhere, Category = Path)
	class USplineComponent* SplinePath;

	int NumWaypoints;
};
