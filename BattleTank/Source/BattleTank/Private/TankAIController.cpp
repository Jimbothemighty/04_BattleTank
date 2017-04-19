// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
//	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"));

	auto ControlledTank = GetControlledTank();

	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has possessed with AI"), *GetPawn()->GetName());
	}
	else if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has not possessed with AI"), *GetPawn()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI Possession report not functioning. See TankPlayerController.cpp"));
	};
};




ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
};


