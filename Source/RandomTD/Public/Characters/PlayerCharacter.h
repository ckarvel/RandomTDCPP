// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UDecalComponent;

UCLASS(Blueprintable)
class ARandomTDPlayerCharacter : public ACharacter
{
	GENERATED_BODY()
private:
  /////////////////////////////////////////////////////////////////////////////////////
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
  UDecalComponent* CursorToWorld;

protected:
  ///////////////////////////////////////////////////////////////////////////
  /// @brief Navigate player to the current cursor location
  void MoveToMouseCursor();

  /////////////////////////////////////////////////////////////////////////////
  ///// @brief Called when right mouse button is pressed
  ///// 
  ///// Starts the character movement updates in Tick()
  void StartMoving() { bMoveToMouseCursor = true; }

  /////////////////////////////////////////////////////////////////////////////
  ///// @brief Called when right mouse button is released
  ///// 
  ///// Ends the character movement updates in Tick()
  ///// This is good for performance because character movement is only
  ///// being updated when the player clicks the right mouse button, instead
  ///// of unnecessarily updating pawn movement when the pawn is not moving!
  void StopMoving() { bMoveToMouseCursor = false; }

  int GoldAmount;
  bool bMoveToMouseCursor; ///< True to move character to cursor

public:
	/////////////////////////////////////////////////////////////////////////////////////
	ARandomTDPlayerCharacter();

	//void Init(class ARandomTDPlayerController* Controller);

	/////////////////////////////////////////////////////////////////////////////////////
	virtual void Tick(float DeltaSeconds) override;

	/////////////////////////////////////////////////////////////////////////////////////
	virtual void BeginPlay() override;

  ///////////////////////////////////////////////////////////////////////////
  void SetupInputComponent(UInputComponent* InputComponent);

	/////////////////////////////////////////////////////////////////////////////////////
	FORCEINLINE UDecalComponent* GetCursorToWorld() { return CursorToWorld; }
};
