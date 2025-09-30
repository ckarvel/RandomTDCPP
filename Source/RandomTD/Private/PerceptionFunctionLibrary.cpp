// Fill out your copyright notice in the Description page of Project Settings.


#include "Perception/AISenseConfig.h"
#include "Perception/AISense.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "PerceptionFunctionLibrary.h"


bool UPerceptionFunctionLibrary::SetSightRange(AAIController* Controller, UAIPerceptionComponent* PerceptionComponent, float NewSightRange, float NewLoseSightRange) {
	if (Controller == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Controller == nullptr"));
		return false;
	}

	FAISenseID Id = UAISense::GetSenseID(UAISense_Sight::StaticClass());
	if (!Id.IsValid()) {
		UE_LOG(LogTemp, Error, TEXT("Wrong Sense ID"));
		return false;
	}

	auto Perception = PerceptionComponent;
	if (Perception == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Perception == nullptr"));
		return false;
	}

	auto Config = Perception->GetSenseConfig(Id);
	if (Config == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Config == nullptr"));
		return false;
	}

	auto ConfigSight = Cast<UAISenseConfig_Sight>(Config);

	ConfigSight->SightRadius = NewSightRange;

	// Apply lose range to new radius of the sight
	ConfigSight->LoseSightRadius = NewLoseSightRange;

	Perception->RequestStimuliListenerUpdate();

	return true;
}