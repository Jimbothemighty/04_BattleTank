// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankAIController.h"
// #include "Pawn.h"
#include "Tank.h"  // so we can implement on death
#include "Mortar.h"  // so we can implement on death
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

		auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
		auto ControlledTank = GetPawn();

		if (!ensure(PlayerTank && ControlledTank)) { return; }

		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm

		// Aim towards the player
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		if (!ensure(AimingComponent)) { return; }
		else
		{
			AimingComponent->AimAt(PlayerTank->GetActorLocation());
		}
		
		// TODO fix firing
		if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
		{
			AimingComponent->Fire(); // TODO (make it so fire ONLY when ready) e.g. if Aimdirection = PlayerTank Actor Location then fire.
		}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank))
		{
			UE_LOG(LogTemp, Warning, TEXT("SOMEHOW THERE IS NO POSSESSED TANK!!"));
			return;
		}

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);

		// Subscribe our local method to the tank's death event
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
	UE_LOG(LogTemp, Error, TEXT("AI tank died."));
//	auto TankName = GetPawn()->GetName();
//	UE_LOG(LogTemp, Warning, TEXT("Name: %s. The AI Tank died."), *TankName);
}





