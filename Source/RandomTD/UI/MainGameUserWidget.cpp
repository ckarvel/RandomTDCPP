// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameUserWidget.h"
#include "RandomTD/RandomTDTowerCharacter.h"

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
