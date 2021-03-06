// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"		// generated.h must be the last #include in the list

class AProjectile;
class ALowHealth;
class UTankTurret;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// called by the engine when damage is dealt
	AProjectile* Projectile;

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator,
		AActor * DamageCauser
	) override;

	// returns current health as a % of starting health between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;

//	UPROPERTY(VisibleAnywhere, Category = "Particles")
//		UParticleSystemComponent* SeriouslyDamagedEffect = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankTurret* TurretToSet);

protected:

private:
	// Sets default values for this pawn's properties
	ATank();

	UTankTurret* Turret = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		int32 CurrentHealth;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	double LastHealthRegenerationTime = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		double RegenDelay = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<ALowHealth> LowHealthBlueprint;
};
