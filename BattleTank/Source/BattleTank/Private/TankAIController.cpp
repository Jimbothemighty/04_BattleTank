// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

/*
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
*/

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto AiTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!PlayerTank) { return; }
	else
	{
		// TODO Move towards the player
		AiTank->AimAt(PlayerTank->GetActorLocation()); // Aims at player

//		auto AimD = ATank* AimAt(FVector HitLocation);

//		if (AiTank->AimAt(PlayerTank->GetActorLocation()) = PlayerTank->GetActorLocation())
//		{
			AiTank->Fire(); // TODO (make it so fire ONLY when ready) e.g. if Aimdirection = PlayerTank Actor Location then fire.
							// TODO Limit firing rate
//		}
	}
	return;
}






