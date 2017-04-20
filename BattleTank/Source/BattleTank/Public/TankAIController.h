// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"     // must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override; // beginplay inherited from AActor. overridable since originally declared virtual in AActor

	ATank* GetControlledTank() const;
	
	ATank* GetPlayerTank() const;

	virtual void Tick(float DeltaTime) override;

};
