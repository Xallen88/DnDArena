// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "AbilityActorProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"


AAbilityActorProjectile::AAbilityActorProjectile() : AAbilityActorBase()
{
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(FName("Collision Sphere"));
	if (CollisionSphere)
	{
		RootComponent = CollisionSphere;
		CollisionSphere->InitSphereRadius(30.f);
		CollisionSphere->SetCollisionProfileName(FName("Projectile"));
		CollisionSphere->SetGenerateOverlapEvents(true);
		CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AAbilityActorProjectile::OnOverlapBegin);
	}

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	if (StaticMesh)
	{
		StaticMesh->SetupAttachment(RootComponent);
		StaticMesh->SetCollisionProfileName(FName("NoCollision"));
	}

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	if (MovementComponent)
	{
		MovementComponent->AddToRoot();
		MovementComponent->ProjectileGravityScale = 0.f;
	}
}

void AAbilityActorProjectile::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
}
