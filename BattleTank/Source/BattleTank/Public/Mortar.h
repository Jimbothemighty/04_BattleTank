// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Mortar.generated.h"		// generated.h must be the last #include in the list

class AProjectile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMortarDelegate);

UCLASS()
class BATTLETANK_API AMortar : public APawn
{
	GENERATED_BODY()

public:
	// called by the engine when damage is dealt
	AProjectile* Projectile;

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator,
		AActor * DamageCauser
	) override;

	// returns current health as a % of starting health between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent() const;

	FMortarDelegate OnDeath;

	//	UPROPERTY(VisibleAnywhere, Category = "Particles")
	//		UParticleSystemComponent* SeriouslyDamagedEffect = nullptr;

protected:

private:
	// Sets default values for this pawn's properties
	AMortar();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 StartingHealth = 100;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 CurrentHealth = StartingHealth;

	// Called every frame
	//	virtual void Tick(float DeltaTime) override;
};
