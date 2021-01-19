// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PriceMgmtComponent.h"
#include "Components/LevelMgmtComponent.h"
#include "Components/ItemMgmtComponent.h"
#include "Kismet/KismetMathLibrary.h"

/////////////////////////////////////////////////////////////////////////////////////
UPriceMgmtComponent::UPriceMgmtComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, MinPrice(50)
	, MaxPrice(100)
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;
}

///////////////////////////////////////////////////////////////////////////////////////
void UPriceMgmtComponent::BeginPlay()
{
	Super::BeginPlay();
}

///////////////////////////////////////////////////////////////////////////////////////
void UPriceMgmtComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

/////////////////////////////////////////////////////////////////////////////////////
void UPriceMgmtComponent::GeneratePrices()
{
	for (auto& Item : PriceMap)
	{
		Item.Value = UKismetMathLibrary::RandomIntegerInRange(MinPrice, MaxPrice);
	}
}
