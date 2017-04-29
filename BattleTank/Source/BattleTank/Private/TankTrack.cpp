// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit
(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse,
	const FHitResult& Hit
)
{
	DriveTrack(); // Drive the tracks
	// Apply Sideways force
	ApplySidewaysForce();
	// reset throttle
	CurrentThrottle = 0.f;
	
}

void UTankTrack::ApplySidewaysForce()
{
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetOwner()->GetActorRightVector());

//	UE_LOG(LogTemp, Warning, TEXT("Slippage speed is %f"), SlippageSpeed);

	auto DeltaTime = GetWorld()->GetDeltaSeconds();

	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector(); // speed / time

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	auto CorrectionForce = (TankRoot->GetMass() * (CorrectionAcceleration)) / 2;

	TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
//	auto Time = GetWorld()->GetTimeSeconds();
//	auto Name = GetName();
//	UE_LOG(LogTemp, Warning, TEXT("%s: Throttle pressed %f!"), *Name, Throttle)

	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
	DriveTrack();
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() *CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(
		ForceApplied,
		ForceLocation
	);
}
// TODO clamp actual throttle value so player can't over-drive

