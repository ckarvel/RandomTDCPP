// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Enemy/EnemyHealthWidget.h"
#include "Characters/EnemyCharacter.h"

/////////////////////////////////////////////////////////////////////////////////////
UEnemyHealthWidget::UEnemyHealthWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Health(0)
	, MaxHealth(0)
{}
