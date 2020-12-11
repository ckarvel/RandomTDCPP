// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerInteractWidget.h"
#include "RandomTD/RandomTDTowerCharacter.h"

/////////////////////////////////////////////////////////////////////////////////////
UTowerInteractWidget::UTowerInteractWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{}

/////////////////////////////////////////////////////////////////////////////////////
void UTowerInteractWidget::SetSelectedTowerRef(ARandomTDTowerCharacter* TowerActor)
{
	OnSellEvent.Unbind();
	SelectedTowerRef = TowerActor;
	if (!SelectedTowerRef)
		return;
	OnSellEvent.BindUObject(SelectedTowerRef, &ARandomTDTowerCharacter::OnSellTower);
}

/////////////////////////////////////////////////////////////////////////////////////
FString UTowerInteractWidget::GetTowerName()
{
	if (SelectedTowerRef)
		return SelectedTowerRef->GetHumanReadableName();
	return FString();
}

/////////////////////////////////////////////////////////////////////////////////////
void UTowerInteractWidget::OnSell()
{
	OnSellEvent.ExecuteIfBound();
}

/////////////////////////////////////////////////////////////////////////////////////
bool UTowerInteractWidget::HaveValidTowerRef()
{
	// just checking if ref is null is not enough...garbage collection delay??
	if (SelectedTowerRef && !SelectedTowerRef->IsPendingKill())
		return true;
	return false;
}