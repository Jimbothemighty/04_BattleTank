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




ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
};
