// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
// #include "Pawn.h"
#include "TankAIController.generated.h"     // must be the last include

// Forward Declarations
class UTankMovementComponent;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	UTankMovementComponent* TankMovementComponent;
	UTankAimingComponent* TankAimingComponent;
	ATankAIController* TankAIController;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000.0f; // TODO check radius in metres

private:
	virtual void BeginPlay() override; // beginplay inherited from AActor. overridable since originally declared virtual in AActor

	virtual void Tick(float DeltaTime) override;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossessedTankDeath();

};
