// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration (links to TankBarrel.h/.cpp)

class UTankBarrel;
class UTankTurret;	//Turrret

// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8 { Locked, Aiming, Reloading };

// Holds parameters for barrel's properties and elevate method
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()



public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel *BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

//	UFUNCTION(BlueprintCallable, Category = Firing)
//		void Fire();

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
		EFiringStatus FiringStatus = EFiringStatus::Aiming;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);	//Turrret

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;	//Turrret

	double LastFireTime = 0;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSeconds = 3.0f;  // TODO find sensible default

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 100000.0f;  // TODO find sensible default
/*
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;
*/
};
