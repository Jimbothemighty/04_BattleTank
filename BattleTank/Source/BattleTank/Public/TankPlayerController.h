// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"   // must be the last include

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UTankAimingComponent* TankAimingComponent;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:

	virtual void BeginPlay() override; // beginplay inherited from AActor. overridable since originally declared virtual in AActor

	virtual void Tick(float DeltaTime) override;


	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation) const;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
		float CrosshairYLocation = 0.3333f;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000.0f;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
		void OnTankDeath();

//	virtual void StartSpectatingOnly() override;

};