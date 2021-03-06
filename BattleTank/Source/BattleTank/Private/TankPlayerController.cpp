// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Tank.h"  // so we can implement on death

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
//	auto ControlledTank = GetPawn();

//	if (!ensure(ControlledTank)) { return; }
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("%s has been possessed by Player"), *GetPawn()->GetName());
//	};

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair(); // TODO <- check appropriate location and usage
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // Out parameter
	
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);

//	UE_LOG(LogTemp, Error, TEXT("got hit?: %i"), bGotHitLocation);

	if (bGotHitLocation) // Has "side-effect", is going to line trace
	{
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	// GetViewportSize is an Unreal function (not a custom one of mine).
	// I am outputting to custom variables ViewportSizeX and ViewportSizeY.
	// The contents of these variables is calculated by the unreal function GetViewportSize()

	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);  // 
																											  // CrosshairXLocation and CrosshairYLocation are variables defined by me in the .h file. Check UE too as they are "EditAnywhere" UPROPERTYs.
																											  // CrosshairXLocation and CrosshairYLocation are float values representing the % of the screen in x and y directions.
																											  // ScreenLocation contains a 2D vector (FVector2D), so the two values are X and Y. They can later be called via ScreenLocation.X and ScreenLocation.Y.

	FVector LookDirection;	/// declared
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that lookDirection, and see what we hit.
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return false;
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
	// Via DeprojectScreenPositionToWorld (Unreal function), the 2D screen position (ScreenLocation)
	// is converted to world space 3D position and direction (variable LookDirection).
	// The outputted variable value is LookDirection
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	// GetVectorHitLocaton inputs LookDirection (sourced from the calling of function GetLookDirection() in GetSightRayHitLocation().
	// I then perform a line trace (Unreal function).
	// We start at the camera location (StartLocation)
	// We then trace out from the camera location to the LookDirection * the range (LineTraceRange variable from .h file [it is EditAnywhere UPROPERTY])
	// Hit type is ECC_Visibility so any object marks a hit.
	// The line trace returns HitResult which is a FHitResult (as was required by the LineTraceSingleByChannel() function).
	// must convert this to an FVector so output HitResult.Location (which is an FVector) to variable HitLocation (also an FVector).
	// HitLocation value from here is then available to GetSightRayHitLocation(), which is used in AimTowardsCrosshair() and logs the FVector to a UE_LOG then called in Tick().

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
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank))
		{
//			UE_LOG(LogTemp, Warning, TEXT("SOMEHOW THERE IS NO POSSESSED TANK!!"));
			return;
		}
		
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);

		// Subscribe our local method to the tank's death event
	}
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
	UE_LOG(LogTemp, Error, TEXT("Name. THE PLAYER TANK DIED WHOOP WHOOP!"));
}
/*
void ATankPlayerController::StartSpectatingOnly()
{
//	FString TankName = GetPawn()->GetName();
	UE_LOG(LogTemp, Error, TEXT("Name. THE PLAYER TANK DIED WHOOP WHOOP!"));
//	UE_LOG(LogTemp, Error, TEXT("Name: %s. THE PLAYER TANK DIED WHOOP WHOOP!"), *TankName);

	ChangeState(NAME_Spectating);
	PlayerState->bIsSpectator = true;
	PlayerState->bOnlySpectator = true;
	bPlayerIsWaiting = false; // Can't spawn, we are only allowed to be a spectator.
};
*/
