// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Game/MainGameUserWidget.h"
#include "Characters/TowerCharacter.h"

/////////////////////////////////////////////////////////////////////////////////////
UMainGameUserWidget::UMainGameUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, TowerVisibility(false)
{
}

/////////////////////////////////////////////////////////////////////////////////////
void UMainGameUserWidget::SetupTowerUI(ARandomTDTowerCharacter* TowerActor)
{
	if (!TowerActor)
		TowerVisibility = false;
	else
		TowerVisibility = true;
	SetTowerReference(TowerActor);
}
