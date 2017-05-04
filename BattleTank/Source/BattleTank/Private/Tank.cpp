// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"
#include "TankTurret.h"
#include "LowHealth.h"
#include "Tank.h"

// Sets default values
ATank::ATank()

{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

//	SeriouslyDamagedEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("Seriously Damaged Particle Effect"));
//	SeriouslyDamagedEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
//	SeriouslyDamagedEffect->bAutoActivate = false;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

//	UE_LOG(LogTemp, Warning, TEXT("DamageAmount=%f, DamageToApply=%i"), DamageAmount, DamageToApply);

	CurrentHealth = CurrentHealth - DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
//		UE_LOG(LogTemp, Warning, TEXT("Broadcasting Death of Tank"));
	}
	return DamageToApply;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

void ATank::Initialise(UTankTurret *TurretToSet)
{
	if (!ensure(TurretToSet)) {
		UE_LOG(LogTemp, Error, TEXT("Turret not set"));
		return; }
	Turret = TurretToSet;
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentHealth < 41)
	{
//	UE_LOG(LogTemp, Warning, TEXT("WARNING LOW HEALTH"));

	if (!ensure(Turret))
	{
		UE_LOG(LogTemp, Warning, TEXT("No turret for spawning damage smoke"));
		return;
	}
	// spawn a projectile at the socketlocation on the barrel

	UE_LOG(LogTemp, Error, TEXT("turret spawned"));
	auto LowHealth = GetWorld()->SpawnActor<ALowHealth>(
		LowHealthBlueprint,
		Turret->GetSocketLocation(FName("DamageLocation")),
		Turret->GetSocketRotation(FName("DamageLocation"))
		);
	}


	if ((CurrentHealth < 100) && (CurrentHealth > 0))
	{
		if ((FPlatformTime::Seconds() - LastHealthRegenerationTime) > RegenDelay)
		{
			UE_LOG(LogTemp, Warning, TEXT("+ 5 health"));
			LastHealthRegenerationTime = FPlatformTime::Seconds();
			CurrentHealth++;
		}
	}

}

