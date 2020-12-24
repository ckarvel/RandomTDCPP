// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PropSelectWidget.generated.h"

DECLARE_DELEGATE_OneParam(FOnPropSelect, int);

/////////////////////////////////////////////////////////////////////////////////////
/// @remark Delegate binding happens in constructor. This can cause a crash if UI is
/// constructed before dependencies.
UCLASS()
class RANDOMTD_API UPropSelectWidget : public UUserWidget
{
  GENERATED_BODY()

public:
  /////////////////////////////////////////////////////////////////////////////////////
  UPropSelectWidget(const FObjectInitializer& ObjectInitializer);

  /////////////////////////////////////////////////////////////////////////////////////
  UFUNCTION(BlueprintCallable, Category = "Base")
  void CallDelegate(int Index);

  FOnPropSelect OnPropSelectEvent;
};
