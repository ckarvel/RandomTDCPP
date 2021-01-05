// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TDCameraManager.generated.h"


class ACameraActor;
class UInputComponent;
class ARandomTDPlayerController;
/**
 * 
 */
UCLASS()
class RANDOMTD_API UTDCameraManager : public UObject
{
  GENERATED_UCLASS_BODY()
	
private:
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

	ACameraActor* PlayerCamera;
  ARandomTDPlayerController* MyController;

protected:
  UPROPERTY(EditAnywhere, Category = Camera)
  float CameraMovementSpeed; ///< How fast the camera pans

public:
  ///////////////////////////////////////////////////////////////////////////
  void Init(ARandomTDPlayerController* PC);

///////////////////////////////////////////////////////////////////////////
  void SetupInputComponent(UInputComponent* InputComponent);
};
