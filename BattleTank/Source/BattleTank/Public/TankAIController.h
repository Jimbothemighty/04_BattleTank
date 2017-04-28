// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"     // must be the last include

// Forward Declarations
class ATank;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override; // beginplay inherited from AActor. overridable since originally declared virtual in AActor
/*
	ATank* GetControlledTank() const;

	ATank* GetPlayerTank() const;
*/
	virtual void Tick(float DeltaTime) override;

	UTankMovementComponent* TankMovementComponent;

private:
	float AcceptanceRadius = 3000.0f; // TODO check radius in cm
};
