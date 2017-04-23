// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"		// generated.h must be the last #include in the list

class UTankBarrel;  // Forward Declaration (links to TankBarrel.h/.cpp)
class UTankTurret;  // Forward Declaration (links to TankBarrel.h/.cpp)
class UTankAimingComponent;   // Forward Declaration (links to TankBarrel.h/.cpp)

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;   // this means we can refer to TankAimingComponent member functions


private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
		// NO TICKING

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 100000.0f;  // TODO find sensible default

};
