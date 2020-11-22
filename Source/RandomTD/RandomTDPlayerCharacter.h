// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RandomTDPlayerCharacter.generated.h"

UCLASS(Blueprintable)
class ARandomTDPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARandomTDPlayerCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	/** Returns Camera subobject **/
	FORCEINLINE class UCameraComponent* GetPlayerCamera() { return PlayerCamera; }

private:

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

	/** Camera controlled by PlayerController */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCamera;
};
