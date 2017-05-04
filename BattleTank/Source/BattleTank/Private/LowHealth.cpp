// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "LowHealth.h"


// Sets default values
ALowHealth::ALowHealth()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	SeriouslyDamagedEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("Seriously Damaged Particle Effect"));
	SeriouslyDamagedEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SeriouslyDamagedEffect->bAutoActivate = false;

}

// Called when the game starts or when spawned
void ALowHealth::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALowHealth::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

