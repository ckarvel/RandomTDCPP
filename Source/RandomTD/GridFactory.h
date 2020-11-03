// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridBase.h"
#include "GridFactory.generated.h"

UCLASS()
class RANDOMTD_API AGridFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridFactory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = Grid)
	void SetupGridArray(TSubclassOf<AGridBase> BP);

	void HighlightGrid(AActor* Grid);

	UPROPERTY(Category = GridSetup, EditAnywhere)
	int Grid_X;
	UPROPERTY(Category = GridSetup, EditAnywhere)
	int Grid_Y;
	UPROPERTY(Category = GridSetup, VisibleAnywhere, BlueprintReadOnly)
	int GridSize; // based on box extent


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerController)
	TSubclassOf<AGridBase> GridBaseClass; // from blueprint
private:


	TArray<AGridBase*> GridBaseList;
	AGridBase* LastTarget; // last tile that was highlighted so we can turn it off
};
