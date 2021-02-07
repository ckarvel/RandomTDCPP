// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UDecalComponent;
class UCameraComponent;

///////////////////////////////////////////////////////////////////////////
UCLASS(Blueprintable)
class ARandomTDPlayerCharacter : public ACharacter
{
	GENERATED_BODY()
private:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
  UDecalComponent* CursorToWorld;

public:
	/////////////////////////////////////////////////////////////////////////////////////
	ARandomTDPlayerCharacter();

	/////////////////////////////////////////////////////////////////////////////////////
	virtual void Tick(float DeltaSeconds) override;

	/////////////////////////////////////////////////////////////////////////////////////
	virtual void BeginPlay() override;

  ///////////////////////////////////////////////////////////////////////////
  /// @brief Navigate player to the current cursor location
  void MoveToMouseCursor();

  /////////////////////////////////////////////////////////////////////////////////////
  UFUNCTION(BlueprintCallable, Category = Camera)
  UCameraComponent* GetPlayerCamera();

  UCameraComponent* PlayerCamera;

  UPROPERTY(EditAnywhere, Category = Camera)
  FTransform InitialCamLocation;
};
