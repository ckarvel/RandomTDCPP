// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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
/// @bug
/// - RANDOM crashes from PlayerTick (line 105) with "exception access violation"
/// - IsTowerInProgress crashes with "assertion on index >=0"
/// - lerp highlighting of objects (clicking vs hovering looks a bit diff)
/// - holding prop over tower ignores grid - make it so when prop is up, ignore tower
/// @todo
/// * cancel prop with right-click
/// * Fix the enemy walk pathing... doesnt run completely in center.
/// * Rectangle selection of towers
/// * make invalid grids
/// * "Select tower"->"Ctrl"->"Select duplicate tower"->"Q": Destroy the tower first-clicked ("Merge" step 1)
/// @todo
/// Complete:
/// - "Select tower"->"delete" button: Destroy selected tower
/// - "Q"->Left-click on invalid grid: Do nothing
/// - Select multiple towers with ctrl
/// - "Q": Spawn mystery prop 
/// - "Q"->Mouse Hover: Grids highlight green for valid, red for invalid
/// - "Q"->Left-click on valid grid: Spawn tower, destroy prop
/// - Left Click / Mouse Hover: Select/Highlight tower
UCLASS()
class ARandomTDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	///////////////////////////////////////////////////////////////////////////
	/// @brief Set default mouse cursor settings.
	ARandomTDPlayerController();

protected:
	///////////////////////////////////////////////////////////////////////////
	/// @brief  Setup bind actions and axis mappings.
	virtual void SetupInputComponent() override;

	///////////////////////////////////////////////////////////////////////////
	/// @brief Called when game starts or when spawned.
	/// 
	/// All actors in the level exist at this point so
	/// it is safe to store references to other actors here.
	void BeginPlay() override;

	///////////////////////////////////////////////////////////////////////////
	/// @brief Handles elements of the game that requires
	/// an update every tick, e.g character movement.
	/// @param DeltaTime How much time has passed since the last tick
	virtual void PlayerTick(float DeltaTime) override;

	///////////////////////////////////////////////////////////////////////////
	/// @brief Navigate player to the current cursor location
	void MoveToMouseCursor();

	///////////////////////////////////////////////////////////////////////////
	/// @brief Navigate the mystery prop to current cursor location
	void MovePropToCursor();

	///////////////////////////////////////////////////////////////////////////
	/// @brief Pans the camera forward or backwards based on AxisValue
	/// 
	/// Called every tick
	/// @param AxisValue 1 Forward
	/// -1 Backwards
	/// 0 No movement
	void MoveCameraForward(float AxisValue);

	///////////////////////////////////////////////////////////////////////////
	/// @brief Pans the camera right or left based on AxisValue
	/// 
	/// Called every tick
	/// @param AxisValue 1 Right
	/// -1 Left
	/// 0 No movement
	void MoveCameraRight(float AxisValue);

	///////////////////////////////////////////////////////////////////////////
	/// @brief Called when player presses the left mouse button
	/// 
	/// Multiple behaviors depending existing actors
	/// @todo Figure out behaviors
	//UFUNCTION(BlueprintImplementableEvent, Category = "Action")
	void OnInteractPressed();

	///////////////////////////////////////////////////////////////////////////
	/// @brief Called when player releases the left mouse button
	/// @todo Is this the right function for drag-selection?
	UFUNCTION(BlueprintImplementableEvent, Category = "Action")
	void OnInteractReleased();

	///////////////////////////////////////////////////////////////////////////
	/// @brief Called when player presses Ctrl
	///
	///  Enables user to select multiple towers to perform some action
	void OnMultiSelectPressed();

	///////////////////////////////////////////////////////////////////////////
	/// @brief Called when player releases Ctrl
	void OnMultiSelectReleased();

	///////////////////////////////////////////////////////////////////////////
	/// @brief Called when the player presses "Q" to create a basic tower.
	/// 
	/// This will spawn the mystery prop under the cursor
	void OnCreateBasicTowerPressed();

	///////////////////////////////////////////////////////////////////////////
	/// @brief Called when right mouse button is pressed
	/// 
	/// Starts the character movement updates in Tick()
	/// 
	/// @remark This is implemented by blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterMovement")
	void OnSetDestinationPressed();

	///////////////////////////////////////////////////////////////////////////
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

	///////////////////////////////////////////////////////////////////////////
	/// @brief Remove mystery prop from the world
	UFUNCTION(BlueprintCallable, Category = "TowerActions")
	void DestroyProp();

	///////////////////////////////////////////////////////////////////////////
	/// @brief Spawn mystery prop. This is implemented in BP and called from here (C++)
	/// @see OnCreateBasicTowerPressed()
	UFUNCTION(BlueprintImplementableEvent, Category = "Mystery")
	void SpawnMystery();

	void OnTowerSelected(class ARandomTDTowerCharacter* SelectedTower);

	bool bMoveToMouseCursor; ///< True to move character to cursor

	bool bTowerRequested; ///< User pressed Q

	bool bCtrlPressed; ///< User pressed Ctrl (Multi-select)

	class ARandomTDPlayerCharacter* PlayerRef;

	class ARandomTDTowerFactory* TowerFactoryRef; ///< Reference to TowerFactory that can be accessed by Blueprint

	class ARandomTDGridFactory* GridFactoryRef;

	UPROPERTY(BlueprintReadWrite, Category = "Tower")
	class AActor* MysteryPropRef; ///< Reference is set by BP. This allows us to easily change prop asset
																///< for cosmetic purposes in the future.

	TArray<class ARandomTDTowerCharacter*> TowersSelectedList;

public:
	///////////////////////////////////////////////////////////////////////////
	/// @brief PlayerController will set character's position every tick when Value is
	/// set to true.
	UFUNCTION(BlueprintCallable, Category = "CharacterMovement")
	void SetMoveToCursor(bool Value);

	///////////////////////////////////////////////////////////////////////////
	/// @brief Gets Mouse cursor hit on custom object types, Grid and Tower
	/// @param UseChannel If True, Only get the Mouse cursor hit on object type of Channel
	/// @param Channel Object type to get hit result on
	/// @return Hit Result from cursor
	FHitResult GetHitOnCustomObjectTypes(bool UseChannel=false, ECollisionChannel Channel=ECC_WorldStatic);

	UPROPERTY(EditAnywhere, Category = Camera)
	float CameraMovementSpeed; ///< How fast the camera pans

	TArray<TEnumAsByte<EObjectTypeQuery>> m_CustomObjectTypes; ///< The object types we created, Grid and Tower

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	class UMainGameUserWidget* MainGameUI;
};
/*
Notes
-------
	1. SpawnActor:
		(ACameraActor*)GetWorld()->SpawnActor(ACameraActor::StaticClass(), &Location, &Rotation);

	2. Rotation order:
		Pitch, Yaw, Roll

	3. UnrealEditor.exe crashes on startup
		If crash on start, debug by running VS in DevelopmentEditor

	4. GetActorOfClass:
		(ARandomTDTowerFactory*) UGameplayStatics::GetActorOfClass(GetWorld(), ARandomTDTowerFactory::StaticClass());

	5. Blueprints do not support uint32/16... just use int if need to expose to blueprint

	6. UE_LOG(LogRandomTD, Log, TEXT("Key: %d %s"), i, *BlackboardAsset->Keys[i].EntryName.ToString());

	7. class is required in front of variable declarations is forward declaring!!! means that you didnt include header
	so we gon forward declare so compiler knows.
*/
