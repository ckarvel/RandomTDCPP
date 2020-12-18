// Fill out your copyright notice in the Description page of Project Settings.

#include "PropManager.h"
#include "RandomTD/RandomTDPlayerController.h" // who else includes pc?

#define GridTraceChannel ECC_GameTraceChannel1
#define TowerTraceChannel ECC_GameTraceChannel2

///////////////////////////////////////////////////////////////////////////
void APropManager::Init(ARandomTDPlayerController* Ref)
{
	MyController = Ref; // should be const ptr.. this class only reads
}

/////////////////////////////////////////////////////////////////////////////////////
void APropManager::MovePropToCursor()
{
	if (MyController == nullptr)
		return;

	FHitResult Hit = MyController->GetHitOnCustomObjectTypes(true, GridTraceChannel);
	// TODO: constrain cursor movement within grid so
	// prop will move even when cursor is outside the grid
	if (Hit.bBlockingHit) // TODO: if grid hit
	{
		MysteryPropRef->SetActorLocation(Hit.ImpactPoint);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
void APropManager::DestroyProp()
{
	MysteryPropRef->Destroy();
}