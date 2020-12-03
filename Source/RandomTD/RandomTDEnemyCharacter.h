// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RandomTDEnemyCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FOnHealthChange, int);
// frozen, slowed, hexed??, but importantly -> death & despawn // figure out how to do enum...
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStateChange, ARandomTDEnemyCharacter*);

/////////////////////////////////////////////////////////////////////////////////////
/// @class ARandomTDEnemyCharacter
/// @brief Enemy base character class.
/// @details Contains a master list of all spawned Enemies which is updated when they
/// are despawned.
UCLASS()
class RANDOMTD_API ARandomTDEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/////////////////////////////////////////////////////////////////////////////////////
	ARandomTDEnemyCharacter();

	/////////////////////////////////////////////////////////////////////////////////////
	virtual void Tick(float DeltaTime) override;
	
	/////////////////////////////////////////////////////////////////////////////////////
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Returns the next or last waypoint in the Spline Path depending on where the
	/// Enemy actor is on the Path.
	/// @details Compares @ref CurrentWaypointIndex to the number of points in the Spline
	/// Path to determine if the actor is at the end. If so, the last waypoint is returned
	/// and a OnStateChange is broadcast with "Finished Path" state. Otherwise,
	/// CurrentWaypointIndex is incremented and returned.
	/// @see CurrentWaypointIndex
	FVector GetNextWaypoint();
	
	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Called when this Enemy actor receives damage. (specifically ApplyDamage)
	/// @details Compares @c Damage to @ref Health to see if Enemy is dead. If so, OnStateChange
	/// is broadcast with "Dead" state. Otherwise, @c Health is subtracted by @c Damage.
	/// @details In both cases, OnHealthChange is executed to notify that health value has changed.
	/// @see UEnemyHealthWidget
	float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyBase")
	float MaxWalkSpeed; ///< Base walking speed for an Enemy.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyBase")
	int MaxHealth; ///< Max Base Health for Enemy.
	
	FOnHealthChange OnHealthChangeEvent; ///< Delegate called when @ref Health changes.

	static FOnStateChange OnStateChangeEvent; ///< Delegate called when Enemy is dead or
																						///< at the end of Spline Path.

protected:
	////////////////////////////////////////////////////////////////////////////////////
	/// @brief Bind @ref UEnemyHealthWidget::SetHealth to @ref OnHealthChangeEvent
	virtual void BeginPlay() override;

	/////////////////////////////////////////////////////////////////////////////////////
	/// @brief Set properties here that rely on instance-editable values.
	/// @details @c GetCharacterMovement()->MaxWalkSpeed is set by @ref MaxWalkSpeed.
	/// If we were to set this in constructor and @c MaxWalkSpeed is changed in an instance,
	/// GetCharacterMovement()->MaxWalkSpeed would not be updated.
	virtual void PostInitializeComponents() override;

	UPROPERTY(EditAnywhere, Category = "EnemyBase")
	class UWidgetComponent* HealthWidgetComponent; ///< UI widget component that contains
																								 ///< @ref HealthWidget

	class UEnemyHealthWidget* HealthWidget; ///< Base class for the UI widget that shows
																		      ///< the Enemy's Health bar.

	UPROPERTY(BlueprintReadWrite, Category = "EnemyBase")
	int Health; ///< Enemy health. When == 0, actor will be destroyed.
	
	int CurrentWaypointIndex; ///< The Enemy's current location relative to Spline Path.
};
