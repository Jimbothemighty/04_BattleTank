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

	// Sets default values for this component's properties
	UTankAimingComponent();
/*
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);	//Turrret
*/
	// TODO add SetTurretReference

	void AimAt(FVector HitLocation, float LaunchSpeed);

	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);	//Turrret

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialise(UTankBarrel *BarrelToSet, UTankTurret* TurretToSet);

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
		EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;	//Turrret

};
