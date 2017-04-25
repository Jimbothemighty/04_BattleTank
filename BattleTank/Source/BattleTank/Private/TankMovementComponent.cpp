// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"



void UTankMovementComponent::IntendMoveForward(float Throw)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: Intend move forwards %f"), *Name, Throw)

	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(Throw);
	
		// clamp double speed (due to dual control use)
}
	

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
		LeftTrack = LeftTrackToSet;
		RightTrack = RightTrackToSet;

		
	
}