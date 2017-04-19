// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto TargetingPlayerTank = GetPlayerTank();

	if (TargetingPlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank name: %s is targetting player tank: %s"), *GetPawn()->GetName(), *(TargetingPlayerTank->GetName()));
	}
	else if (!TargetingPlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AI Tank name: %s is not targetting a player."), *GetPawn()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AI targetting player report not functioning. See TankAIController.cpp"));
	};

};




ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
};

ATank* ATankAIController::GetPlayerTank() const
{
//	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
//	if (!PlayerPawn) { return nullptr; };
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());  // can also return PlayerPawn (as per Ben). But I have kept my original code.
};


