// Fill out your copyright notice in the Description page of Project Settings.


#include "RoundInfoWidget.h"
#include "RandomTD/RandomTDGameMode.h"
#include "RandomTD/RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
URoundInfoWidget::URoundInfoWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, CurrentLevel(0)
	, LevelElapsedTime(0.0)
{
}

void URoundInfoWidget::Init()
{
	kSecondsPerLevel = ARandomTDGameMode::GetLevelManager()->GetSecondsPerLevel();
	kPreLevelSeconds = ARandomTDGameMode::GetLevelManager()->GetPreLevelSeconds();
	//#ifdef UE_BUILD_DEBUG
	//	UE_LOG(LogRandomTD, Log, TEXT("UMainGameUserWidget::Constructor"));
	//#endif

	// this may cause a crash in unreal. this should be set in BeginPlay or something
	// it hasn't crashed here yet tho... so ill just hold off.
	ARandomTDGameMode::GetLevelManager()->LevelStartEvent.AddUObject(this, &URoundInfoWidget::SetCurrentLevel);
	ARandomTDGameMode::GetLevelManager()->LevelSecondElapsedEvent.AddUObject(this, &URoundInfoWidget::SetLevelTime);
}