// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"



void UTankMovementComponent::IntendMoveForward(float Throw)
{
	auto Name = GetName();
//	UE_LOG(LogTemp, Warning, TEXT("%s: Intend move forwards %f"), *Name, Throw)

	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(Throw);
	
		// clamp double speed (due to dual control use)


}


void UTankMovementComponent::IntendTurnRight(float Throw)
{
	auto Name = GetName();
//	UE_LOG(LogTemp, Warning, TEXT("%s: Intend move left/right %f"), *Name, Throw)

	RightTrack->SetThrottle(-Throw);
	LeftTrack->SetThrottle(Throw);

	// clamp double speed (due to dual control use)
}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
		LeftTrack = LeftTrackToSet;
		RightTrack = RightTrackToSet;

		
	
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankName = GetOwner()->GetName();
	auto MoveVelocityString = MoveVelocity.GetSafeNormal().ToString();
	UE_LOG(LogTemp, Error, TEXT("%s: vectoring to %s"), *TankName, *MoveVelocityString);

	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	//auto AIRightIntention = MoveVelocity.GetSafeNormal();
	//auto TankRight = GetOwner()->GetActorRightVector().GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	//auto RightThrow = FVector::DotProduct(TankRight, AIRightIntention);
	auto TurnThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

	IntendMoveForward(ForwardThrow);
	//IntendMoveRight(RightThrow);
	IntendTurnRight(TurnThrow);
}