// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * // TankTrack is used to set maximum driving force, and to apply forces to the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);

	//	float Throttle = 0.0f; // sensible default

	// Max force per track in newtons
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 4000000.0f; // assume 40000kg tank and acceleration 1g (10m/s^2) and F=M*A)

private:
	UTankTrack();

	virtual void BeginPlay() override;

//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ApplySidewaysForce();

	UFUNCTION()
		void OnHit(
			UPrimitiveComponent* HitComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComponent,
			FVector NormalImpulse,
			const FHitResult& Hit
		);

	void DriveTrack();

	float CurrentThrottle = 0.f;
};
