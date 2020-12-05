// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomTDTowerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/TowerInteractWidget.h"
#include "RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDTowerCharacter::ARandomTDTowerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SetCanBeDamaged(false);
	TowerWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("TowerWidget");
	TowerWidgetComponent->SetupAttachment(RootComponent);
	TowerWidgetComponent->SetDrawAtDesiredSize(true);
	TowerWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// get reference to UI tower component
	TowerWidget = Cast<UTowerInteractWidget>(TowerWidgetComponent->GetUserWidgetObject());
	if (!TowerWidget)
	{
#ifdef UE_BUILD_DEBUG
		UE_LOG(LogRandomTD, Error, TEXT("ARandomTDTowerCharacter::TowerWidget NULL!"));
#endif
		return;
	}

	// initialize UI tower values
	// attack speed / defense / etc.
	
	// add a dispatcher for updating our UI when health changes (thats why its not static)
	TowerWidget->OnSellEvent.BindUObject(this, &ARandomTDTowerCharacter::OnSellTower);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDTowerCharacter::OnSellTower()
{
	Destroy();
}

/////////////////////////////////////////////////////////////////////////////////////
//void ARandomTDTowerCharacter::Attack()
//{
//	UGameplayStatics::ApplyDamage(EnemyToAttack, 5.0, NULL, NULL, NULL);
//}

//static float ApplyDamage(AActor* DamagedActor, float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<class UDamageType> DamageTypeClass);
