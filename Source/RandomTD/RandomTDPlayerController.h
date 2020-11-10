// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TowerFactory.h"
#include "GridFactory.h"
#include "RandomTDPlayerController.generated.h"

/// @class ARandomTDPlayerController
/// @brief The PlayerController for Random TD
/// 
/// Handles player input
///
///	Notes:
/// - In this game, the player doesn't interact with pawn.
/// 
/// Players abilities :
/// - Object creation(tower / crop)
/// - Tower / Crop placement
/// - Item selection
/// - Highlighting items(including enemies / towers)
/// - Camera movement with mouse cursor
/// - Hover and see info (?)
/// 
/// @todo 
/// - "Q"->Left-click on invalid grid: Do nothing
/// - Left-click on tower: Highlight tower as "selected" (requires UI)
/// - "Select tower"->"E": Destroy selected tower
/// - "Select tower"->"Ctrl"->"Select duplicate tower"->"Q": Destroy the tower first-clicked ("Merge" step 1)
/// - Rectangle selection of towers
/// @todo
/// Complete:
/// - "Q": Spawn mystery prop 
/// - "Q"->Mouse Hover: Grids highlight green for valid, red for invalid
/// - "Q"->Left-click on valid grid: Spawn tower, destroy prop
UCLASS()
class ARandomTDPlayerController : public APlayerController
{
	GENERATED_BODY()

	///////////////////////////////////////////////////////////////////////////
	// SETUP
	///////////////////////////////////////////////////////////////////////////
public:
	/// @brief Set default mouse cursor settings.
	ARandomTDPlayerController();

protected:
	/// @brief  Setup bind actions and axis mappings.
	virtual void SetupInputComponent() override;

	/// @brief Called when game starts or when spawned.
	/// 
	/// All actors in the level exist at this point so
	/// it is safe to store references to other actors here.
	void BeginPlay() override;

	/// @brief Handles elements of the game that requires
	/// an update every tick, e.g character movement.
	/// @param DeltaTime How much time has passed since the last tick
	virtual void PlayerTick(float DeltaTime) override;

	///////////////////////////////////////////////////////////////////////////
	// ON-TICK
	///////////////////////////////////////////////////////////////////////////

	/// @brief Navigate player to the current cursor location
	void MoveToMouseCursor();

	/// @brief Navigate the mystery prop to current cursor location
	void MovePropToCursor();

	/// @brief Pans the camera forward or backwards based on AxisValue
	/// 
	/// Called every tick
	/// @param AxisValue 1 Forward
	/// -1 Backwards
	/// 0 No movement
	void MoveCameraForward(float AxisValue);

	/// @brief Pans the camera right or left based on AxisValue
	/// 
	/// Called every tick
	/// @param AxisValue 1 Right
	/// -1 Left
	/// 0 No movement
	void MoveCameraRight(float AxisValue);

	///////////////////////////////////////////////////////////////////////////
	// ACTION FUNCTIONS
	///////////////////////////////////////////////////////////////////////////

	/// @brief Called when player presses the left mouse button
	/// 
	/// Multiple behaviors depending existing actors
	/// @todo Figure out behaviors
	UFUNCTION(BlueprintImplementableEvent, Category = "Action")
	void OnPerformActionPressed();

	/// @brief Called when player releases the left mouse button
	/// @todo Is this the right function for drag-selection?
	UFUNCTION(BlueprintImplementableEvent, Category = "Action")
	void OnPerformActionReleased();

	/// @brief Called when the player presses "Q" to create a basic tower.
	/// 
	/// This will spawn the mystery prop under the cursor
	UFUNCTION(BlueprintImplementableEvent, Category = "TowerActions")
	void OnCreateBasicTowerPressed();

	/// @brief Called when right mouse button is pressed
	/// 
	/// Starts the character movement updates in Tick()
	/// 
	/// @remark This is implemented by blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterMovement")
	void OnSetDestinationPressed();

	/// @brief Called when right mouse button is released
	/// 
	/// Ends the character movement updates in Tick()
	/// This is good for performance because character movement is only
	/// being updated when the player clicks the right mouse button, instead
	/// of unnecessarily updating pawn movement when the pawn is not moving!
	/// 
	/// @remark This is implemented by blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterMovement")
	void OnSetDestinationReleased();

	/// @brief Remove mystery prop from the world
	UFUNCTION(BlueprintCallable, Category = "TowerActions")
	void DestroyProp();

public:
	///////////////////////////////////////////////////////////////////////////
	// SETTERS & GETTERS
	///////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "CharacterMovement")
	void SetMoveToCursor(bool Value);
	UFUNCTION(BlueprintCallable, Category = "TowerActions")
	void SetTowerInProgress(AActor* MysteryProp);
	UFUNCTION(BlueprintCallable, Category = "TowerActions")
	bool IsTowerInProgress();
	UFUNCTION(BlueprintCallable, Category = "Helper")
	FHitResult GetCursorHitResultOnObjectType(ECollisionChannel Channel);

protected:
	bool bMoveToMouseCursor; ///< True to move character to cursor
	class ARandomTDCharacter* PlayerRef;
	UPROPERTY(Category = References, BlueprintReadWrite)
	class ATowerFactory* TowerFactoryRef;
	class AGridFactory* GridFactoryRef;
	class AActor* MysteryPropRef;
public:
	UPROPERTY(EditAnywhere, Category = Camera)
	float CameraMovementSpeed; ///< How fast the camera pans
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