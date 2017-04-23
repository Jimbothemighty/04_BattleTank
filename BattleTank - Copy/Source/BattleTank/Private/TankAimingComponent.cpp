// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
/*
	auto BarrelName = Barrel->GetName();
	auto OurTankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s is aiming at hit location is: %s"), *OurTankName, *HitLocation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("firing at %f"), LaunchSpeed); */

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto OurTankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"), *OurTankName, *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);

	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Moves the barrel in the aimdirection, but only in the y-axis
	// Barrel->GetComponentRotation
/*
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	UE_LOG(LogTemp, Warning, TEXT("Barrel Rotation is %s and Aim Rotation is %s"), *BarrelRotator.ToString(), *AimAsRotator.ToString());
	UE_LOG(LogTemp, Error, TEXT("Delta Rotation is %s"), *DeltaRotator.ToString());

	// 	Barrel->SetRelativeRotation to aimdirection.y   (if cannot output this then simply constrain rotation in x and z in UE blueprint/menus
		// Move the barrel te right amount this frame
			// given a maximum elevation speed, and the frame time

*/
//	UE_LOG(LogTemp, Warning, TEXT("Barrel Rotation is and Aim Rotation is"));
	Barrel->Elevate(5.0f); // TODO remove magic number

}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}