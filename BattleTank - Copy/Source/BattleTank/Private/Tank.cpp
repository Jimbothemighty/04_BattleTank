// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	// No need to protect pointers as added at construction
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ATank::AimAt(FVector HitLocation)  // refers to the Tank.h for function AimAt
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);  // but then the statements pass in the AimAt function from TankAimngComponent.cpp
	// This function statement goes to UTankAimingComponent* TankAimingComponent in the Tank.h file, which is a pointer to the class in TankAimingComponent.h file, which finds the equiv. AimAt function there.
	// Saying TankAimingComponent->AimAt(HitLocation) is the same as saying UTankAimingComponent::AimAt(HitLocation) but this doesn't work even if you add #include "TankAimingComponent.h 
	// It uses the statements from the TankAimingComponent.cpp file and then passes in HitLocation calculated from the TankPlayerController.cpp and TankAIController.cpp files.
	// statements for AimAt are called from TankPlayer/AIController.cpp/h (which are requested from its pawn) Tank.cpp/h (which the pawn gets from it's component) TankAimingComponent.cpp/h
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	// above function from ATank.h outputs BarrelToSet to a staticmeshcomponent class

	TankAimingComponent->SetBarrelReference(BarrelToSet); // Gets SetBarrelReference function from UTankAimingComponent class, which outputs the value of BarrelToSet to the ATank 'setter' function.
	// The TankAimingComponent.cpp version is a 'getter' that gets the value of BarrelToSet from private variable UStaticMeshComponent* Barrel in the .h file.
}
