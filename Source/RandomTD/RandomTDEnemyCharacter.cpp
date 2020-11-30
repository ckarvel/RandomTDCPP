 // Fill out your copyright notice in the Description page of Project Settings.


#include "RandomTDEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/EnemyHealthWidget.h"
#include "RandomTDPathSpline.h"
#include "RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
// Define static delegates
FOnStateChange ARandomTDEnemyCharacter::OnStateChangeEvent;

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDEnemyCharacter::ARandomTDEnemyCharacter()
	: MaxWalkSpeed(300.0)
	, MaxHealth(100)
	, Health(100)
	, CurrentWaypointIndex(0)
{
	PrimaryActorTick.bCanEverTick = false; // no ticking

	SetCanBeDamaged(true);
	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidget");
	HealthWidgetComponent->SetupAttachment(RootComponent);
	HealthWidgetComponent->SetDrawAtDesiredSize(true);
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// get reference to UI health component
	HealthWidget = Cast<UEnemyHealthWidget>(HealthWidgetComponent->GetUserWidgetObject());
	if (!HealthWidget)
	{
#ifdef UE_BUILD_DEBUG
		UE_LOG(LogRandomTD, Error, TEXT("ARandomTDEnemyCharacter::HealthWidget NULL!"));
#endif
		return;
	}

	// initialize UI health values
	HealthWidget->SetHealth(Health);
	HealthWidget->SetMaxHealth(MaxHealth);

	// add a dispatcher for updating our UI when health changes (thats why its not static)
	OnHealthChangeEvent.BindUObject(HealthWidget, &UEnemyHealthWidget::SetHealth);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// configure character movement
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	
	// set health to max
	Health = MaxHealth;
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/////////////////////////////////////////////////////////////////////////////////////
FVector ARandomTDEnemyCharacter::GetNextWaypoint()
{
	int Index = CurrentWaypointIndex;

	if (ARandomTDPathSpline::NumWaypoints <= ++Index)
	{
		// next waypoint is INVALID so don't save index
		// return LAST waypoint
		OnStateChangeEvent.Broadcast(this); // notify despawn
	}
	else
	{
		// next waypoint is VALID so save the index
		// return NEXT waypoint
		CurrentWaypointIndex = Index;
	}
	return ARandomTDPathSpline::GetWaypointAtIndex(CurrentWaypointIndex);
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDEnemyCharacter::ReceiveAnyDamage(float Damage,
																							 const UDamageType* DamageType, 
																							 AController* InstigatedBy,
																							 AActor* DamageCauser)
{
	if (int(Damage) > Health)
	{
		// damage kills us, notify state change
		Health = 0;
		OnStateChangeEvent.Broadcast(this);
	}
	else
	{
		// otherwise, subtract our health by damage taken
		Health -= int(Damage);
	}

	// notify health change either way... just in case
	OnHealthChangeEvent.Execute(Health);
}
