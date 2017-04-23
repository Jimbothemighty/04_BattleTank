// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Moves the barrel in the aimdirection, but only in the y-axis
	// Barrel->GetComponentRotation

	//auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	//auto AimAsRotator = AimDirection.Rotation();
	//auto DeltaRotator = AimAsRotator - BarrelRotator;

	//UE_LOG(LogTemp, Warning, TEXT("Barrel Rotation is %s and Aim Rotation is %s"), *BarrelRotator.ToString(), *AimAsRotator.ToString());
	//UE_LOG(LogTemp, Error, TEXT("Delta Rotation is %s"), *DeltaRotator.ToString());

	// 	Barrel->SetRelativeRotation to aimdirection.y   (if cannot output this then simply constrain rotation in x and z in UE blueprint/menus
	// Move the barrel te right amount this frame
	// given a maximum elevation speed, and the frame time

//	auto Time = GetWorld()->GetTimeSeconds();
//	UE_LOG(LogTemp, Error, TEXT("Time: %f. Barrel Elevate is called at speed %f"), Time, RelativeSpeed);

}
