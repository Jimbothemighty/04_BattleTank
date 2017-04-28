// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"		// generated.h must be the last #include in the list

// Forward Declarations
class UTankBarrel;
class UTankTurret;     
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
//	void AimAt(FVector HitLocation);
/*
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet);
*/
//	UFUNCTION(BlueprintCallable, Category = Firing)
//		void Fire();

protected:

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
		// NO TICKING

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

//	UPROPERTY(EditDefaultsOnly, Category = Firing)
//		float ReloadTimeInSeconds = 3.0f;  // TODO find sensible default

//	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 100000.0f;  // TODO find sensible default

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;
	
	// Local barrel reference for spawning projectile
//	UTankBarrel* Barrel = nullptr;  // TODO remove
};
