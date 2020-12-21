// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RandomTDPlayerCharacter.generated.h"

UCLASS(Blueprintable)
class ARandomTDPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/////////////////////////////////////////////////////////////////////////////////////
	ARandomTDPlayerCharacter();

	//void Init(class ARandomTDPlayerController* Controller);

	/////////////////////////////////////////////////////////////////////////////////////
	virtual void Tick(float DeltaSeconds) override;

	/////////////////////////////////////////////////////////////////////////////////////
	virtual void BeginPlay() override;

	/////////////////////////////////////////////////////////////////////////////////////
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	///////////////////////////////////////////////////////////////////////////
	/// @brief Navigate player to the current cursor location
	void MoveToMouseCursor();

	/////////////////////////////////////////////////////////////////////////////
	///// @brief Called when right mouse button is pressed
	///// 
	///// Starts the character movement updates in Tick()
	///// 
	///// @remark This is implemented by blueprint
	//UFUNCTION(BlueprintImplementableEvent, Category = "CharacterMovement")
	//void OnSetDestinationPressed();

	/////////////////////////////////////////////////////////////////////////////
	///// @brief Called when right mouse button is released
	///// 
	///// Ends the character movement updates in Tick()
	///// This is good for performance because character movement is only
	///// being updated when the player clicks the right mouse button, instead
	///// of unnecessarily updating pawn movement when the pawn is not moving!
	///// 
	///// @remark This is implemented by blueprint
	//UFUNCTION(BlueprintImplementableEvent, Category = "CharacterMovement")
	//void OnSetDestinationReleased();
	
	///////////////////////////////////////////////////////////////////////////
	void SetMoveToCursor(bool Value) { bMoveToMouseCursor = Value; }

	int GoldAmount;

	bool bMoveToMouseCursor; ///< True to move character to cursor

private:
	/////////////////////////////////////////////////////////////////////////////////////
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
};
