// Fill out your copyright notice in the Description page of Project Settings.


#include "PropSelectWidget.h"

/////////////////////////////////////////////////////////////////////////////////////
UPropSelectWidget::UPropSelectWidget(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer)
{
}

void UPropSelectWidget::CallDelegate(int Index)
{
  OnPropSelectEvent.ExecuteIfBound(Index);
}