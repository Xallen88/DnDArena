// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "AbilityActorProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Player/PlayerCharacter.h"


AAbilityActorProjectile::AAbilityActorProjectile() : AAbilityActorBase()
{	
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(FName("Collision Sphere"));
	if (CollisionSphere)
	{
		CollisionSphere->InitSphereRadius(30.f);
		CollisionSphere->SetCollisionProfileName(FName("Projectile"));
		CollisionSphere->SetGenerateOverlapEvents(true);
		CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AAbilityActorProjectile::OnOverlapBegin);
		CollisionSphere->SetupAttachment(RootComponent);
	}
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	if (StaticMesh)
	{				
		StaticMesh->SetCollisionProfileName(FName("NoCollision"));
		if (CollisionSphere)
		{
			StaticMesh->SetupAttachment(CollisionSphere);
		}
	}

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	if (MovementComponent)
	{
		MovementComponent->UpdatedComponent = RootComponent;
		MovementComponent->ProjectileGravityScale = 0.f;
	}
}

void AAbilityActorProjectile::WorldCollision()
{
	// TODO: Gameplaycues
	
	if (HasAuthority())
	{
		OnImpact();
	}
	
	Destroy();
}

void AAbilityActorProjectile::PlayerCollision(AActor* OtherActor)
{
	// TODO: Gameplaycues

	if (HasAuthority())
	{
		UGameplayStatics::ApplyPointDamage(OtherActor, 1.f, GetActorLocation(), FHitResult(), GetInstigatorController(), this, UDamageType::StaticClass());
		
		OnImpact();
	}

	Destroy();
}

void AAbilityActorProjectile::OnImpact()
{
}

void AAbilityActorProjectile::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA<APlayerCharacter>())
	{
		if (!ExcludedPlayers.Contains(OtherActor))
		{
			PlayerCollision(OtherActor);
		}
	}
	else
	{
		WorldCollision();
	}
}
