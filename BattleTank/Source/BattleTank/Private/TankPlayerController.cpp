// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
//	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	auto ControlledTank = GetControlledTank();

	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has possessed by Player"), *GetPawn()->GetName());
	}
	else if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has not possessed by Player"), *GetPawn()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Possession report not functioning. See TankPlayerController.cpp"));
	};
};



void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );

	UE_LOG(LogTemp, Error, TEXT("FUCKING TICKING YO!"));

	AimTowardsCrosshair(); // TODO <- check appropriate location and usage

	return;
};



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
};


void ATankPlayerController::AimTowardsCrosshair()
{
	// TODO <- write function
	// start the tank moving the barrel so that a shot would hit there
	// the crosshair intersects the world

	if (!GetControlledTank()) { return; }

	// Get world location if linetrace through crosshair
	// if it hits the landscape
		// Tell controlled tank to aim at this point
};