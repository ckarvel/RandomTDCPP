// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameUserWidget.h"
#include "RandomTD/RandomTDGameMode.h"
#include "RandomTD/RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
UMainGameUserWidget::UMainGameUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, CurrentRound(0)
	, RoundElapsedTime(0.0)
{
	kSecondsPerRound = ARandomTDGameMode::GetSecondsPerRound();
	kPreRoundSeconds = ARandomTDGameMode::GetPreRoundSeconds();
#ifdef UE_BUILD_DEBUG
	UE_LOG(LogRandomTD, Log, TEXT("UMainGameUserWidget::Constructor"));
#endif

	// this may cause a crash in unreal. this should be set in BeginPlay or something
	// it hasn't crashed here yet tho... so ill just hold off.
	ARandomTDGameMode::RoundStartEvent.AddUObject(this, &UMainGameUserWidget::SetCurrentRound);
	ARandomTDGameMode::RoundSecondElapsedEvent.AddUObject(this, &UMainGameUserWidget::SetRoundTime);
}
/////////////////////////////////////////////////////////////////////////////////////
