// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthWidget.h"
#include "RandomTD/RandomTDEnemyCharacter.h"

/////////////////////////////////////////////////////////////////////////////////////
UEnemyHealthWidget::UEnemyHealthWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Health(0)
	, MaxHealth(0)
{}
