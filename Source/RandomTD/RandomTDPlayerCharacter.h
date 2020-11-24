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
	ARandomTDPlayerCharacter();

	/////////////////////////////////////////////////////////////////////////////////////
	///@brief
	virtual void Tick(float DeltaSeconds) override;

	/////////////////////////////////////////////////////////////////////////////////////
	///@brief
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	/////////////////////////////////////////////////////////////////////////////////////
	///@brief
	FORCEINLINE class UCameraComponent* GetPlayerCamera() { return PlayerCamera; }

private:

	/////////////////////////////////////////////////////////////////////////////////////
	///@brief
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

	/////////////////////////////////////////////////////////////////////////////////////
	///@brief
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCamera;
};
