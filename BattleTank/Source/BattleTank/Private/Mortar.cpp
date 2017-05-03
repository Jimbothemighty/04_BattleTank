// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"
#include "Mortar.h"


// Sets default values
AMortar::AMortar()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//	SeriouslyDamagedEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("Seriously Damaged Particle Effect"));
	//	SeriouslyDamagedEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//	SeriouslyDamagedEffect->bAutoActivate = false;
}

float AMortar::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	//	UE_LOG(LogTemp, Warning, TEXT("DamageAmount=%f, DamageToApply=%i"), DamageAmount, DamageToApply);

	CurrentHealth = CurrentHealth - DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("Broadcasting Death of Mortar"));
	}
	return DamageToApply;
}

// Called when the game starts or when spawned
void AMortar::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float AMortar::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
};

/*

// Called every frame
void AMortar::Tick(float DeltaTime)
{
Super::Tick(DeltaTime);

if (CurrentHealth <= 41)
{
UE_LOG(LogTemp, Warning, TEXT("WARNING LOW HEALTH"));
}
}

*/
