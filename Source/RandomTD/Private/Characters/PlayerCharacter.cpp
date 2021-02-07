// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/PlayerCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "RandomTD/RandomTD.h"

/////////////////////////////////////////////////////////////////////////////////////
ARandomTDPlayerCharacter::ARandomTDPlayerCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	InitialCamLocation.SetLocation(FVector(-565.0, -10.0, 1610.0));
	InitialCamLocation.SetRotation(FQuat(FRotator(-70, 0, 0))); // pitch yaw roll

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	PlayerCamera->bConstrainAspectRatio = false;
	PlayerCamera->SetUsingAbsoluteLocation(true);
	PlayerCamera->SetUsingAbsoluteRotation(true);
	PlayerCamera->SetupAttachment(RootComponent);

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerCamera->SetRelativeLocation(InitialCamLocation.GetLocation());
	PlayerCamera->SetRelativeRotation(InitialCamLocation.GetRotation());
}

/////////////////////////////////////////////////////////////////////////////////////
UCameraComponent* ARandomTDPlayerCharacter::GetPlayerCamera()
{
	return PlayerCamera;
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerCharacter::Tick(float DeltaSeconds)
{
  Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
void ARandomTDPlayerCharacter::MoveToMouseCursor()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			FVector DestLocation = Hit.ImpactPoint;
			float const Distance = FVector::Dist(DestLocation, GetActorLocation());
			// We need to issue move command only if far enough
			// in order for walk animation to play correctly
			if (Distance > 120.0f)
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(PC, DestLocation);
			}
		}
	}
}
