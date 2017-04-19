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



void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );

//	ThePointInSpaceHit();

	AimTowardsCrosshair(); // TODO <- check appropriate location and usage

	return;
};



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
};




void ATankPlayerController::AimTowardsCrosshair()
{
	// TODO <- write function
	// start the tank moving the barrel so that a shot would hit there
	// the crosshair intersects the world

	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("hit location is: %s"), *HitLocation.ToString());
	}
};

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	
	FVector LookDirection;
	if(GetLookDirection(ScreenLocation, LookDirection))
	{
		// TODO Line-trace along that lookDirection, and see what we hit.
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	

	return true;
};


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
//	UE_LOG(LogTemp, Error, TEXT("Hit Direction: %s"), *LookDirection.ToString());
};


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	/// Setup query parameters


	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
		))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else { HitLocation = FVector(0);  return false; };
};

