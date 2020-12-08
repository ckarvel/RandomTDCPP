// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerInteractWidget.h"
#include "RandomTD/RandomTDTowerCharacter.h"

/////////////////////////////////////////////////////////////////////////////////////
UTowerInteractWidget::UTowerInteractWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{}

/////////////////////////////////////////////////////////////////////////////////////
void UTowerInteractWidget::SetSelectedTowerRef(class ARandomTDTowerCharacter* TowerActor)
{
	OnSellEvent.Unbind();
	SelectedTowerRef = TowerActor;
	if (!SelectedTowerRef)
		return;
	OnSellEvent.BindUObject(SelectedTowerRef, &ARandomTDTowerCharacter::OnSellTower);
}

/////////////////////////////////////////////////////////////////////////////////////
void UTowerInteractWidget::OnSell()
{
	OnSellEvent.ExecuteIfBound();
}
