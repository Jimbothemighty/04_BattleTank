// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankAIController.h"
// Depends on movement component via pathfinding system


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
/*
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
*/
};


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto AiTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerTank)) { return; }
	else
	{
		// TODO Move towards the player
		MoveToActor(
			PlayerTank,
			AcceptanceRadius,
			true, true, false
		);

		TankAimingComponent->AimAt(PlayerTank->GetActorLocation()); // Aims at player

// TODO fix firing
//		TankAimingComponent->Fire(); // TODO (make it so fire ONLY when ready) e.g. if Aimdirection = PlayerTank Actor Location then fire.
	}
	return;
}






