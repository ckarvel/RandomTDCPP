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

UCLASS()
class ARandomTDPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	class ATowerManager* TowerManager;
	class APropManager* PropManager;

public:
	///////////////////////////////////////////////////////////////////////////
	/// @brief Set default mouse cursor settings.
	ARandomTDPlayerController();

	///////////////////////////////////////////////////////////////////////////
	/// @brief Gets Mouse cursor hit on custom object types, Grid and Tower
	/// @param UseChannel If True, Only get the Mouse cursor hit on object type of Channel
	/// @param Channel Object type to get hit result on
	/// @return Hit Result from cursor
	FHitResult GetHitOnCustomObjectTypes(bool UseChannel = false, ECollisionChannel Channel = ECC_WorldStatic);

	///////////////////////////////////////////////////////////////////////////
	class UMainGameUserWidget* GetUI();

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
	class ARandomTDPlayerCharacter* MyPawn;
	class ACameraActor* PlayerCamera;

	UPROPERTY(EditAnywhere, Category = Camera)
	float CameraMovementSpeed; ///< How fast the camera pans

	UPROPERTY(BlueprintReadWrite, Category = "Base")
	class UMainGameUserWidget* MainGameUI;
	
	UPROPERTY(EditAnywhere, Category = "Base")
	TSubclassOf<AActor> PropClass;

	TArray<TEnumAsByte<EObjectTypeQuery>> m_CustomObjectTypes; ///< The object types we created, Grid and Tower
};
