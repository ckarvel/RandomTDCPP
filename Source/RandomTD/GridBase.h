// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Math/Color.h"
#include "GridBase.generated.h"

UCLASS()
class RANDOMTD_API AGridBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HighlightGrid();

	void TurnOffGrid();

	UPROPERTY(Category = Grid, VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxComponent;

	UPROPERTY(Category = Grid, VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(Category = Grid, EditAnywhere)
	UMaterialInterface* ParentMaterial;

	UPROPERTY(Category = Grid, EditAnywhere)
	FLinearColor ValidTileColor;

	UPROPERTY(Category = Grid, EditAnywhere)
	FLinearColor InvalidTileColor;

	UPROPERTY(Category = Grid, EditAnywhere)
	bool bIsValidGrid; // can tower be placed on this grid?

private:
	UMaterialInstanceDynamic* DynamicMaterial;
};
