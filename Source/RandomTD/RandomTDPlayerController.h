// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TowerFactory.h"
#include "GridFactory.h"
#include "RandomTDPlayerController.generated.h"

UCLASS()
class ARandomTDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARandomTDPlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	void BeginPlay() override;

	/*
		For TD, the player won't really interact with pawn
		Players abilities:
		- Object creation (tower/crop)
		- Tower/Crop placement
		- Item selection
		- Highlighting items (including enemies/towers)
		- Camera movement with mouse cursor
		- Hover and see info?
	*/

	/*Player-abilities*/
	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();
	void MovePropToCursor();
	void MoveCameraForward(float AxisValue);
	void MoveCameraRight(float AxisValue);
	void OnCreateBasicTowerPressed();
	void OnPerformActionPressed();
	void OnPerformActionReleased();
	void HighlightGrid();

	/*Pawn-related abilities*/
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

public:
	UPROPERTY(EditAnywhere, Category = Camera)
	float CameraMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Prop)
	TSubclassOf<AActor> MysteryPropClass;

private:
	class ARandomTDCharacter* PlayerRef;
	class ATowerFactory* TowerFactoryRef;
	class AGridFactory* GridFactoryRef;

	class AActor* MysteryPropRef;
	float MysteryPropHalfHeight;
	bool bPropActive;
};

/*
Notes
-------
	SpawnActor:
		(ACameraActor*)GetWorld()->SpawnActor(ACameraActor::StaticClass(), &Location, &Rotation);

	Rotation order:
		Pitch, Yaw, Roll

	UnrealEditor.exe crashes on startup
		If crash on start, debug by running VS in DevelopmentEditor

	GetActorOfClass:
		(ATowerFactory*) UGameplayStatics::GetActorOfClass(GetWorld(), ATowerFactory::StaticClass());

	Blueprints do not support uint32/16... just use int if need to expose to blueprint
*/