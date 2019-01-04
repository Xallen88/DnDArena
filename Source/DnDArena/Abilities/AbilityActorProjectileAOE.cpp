// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "AbilityActorProjectileAOE.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

void AAbilityActorProjectileAOE::WorldCollision()
{
	// TODO: GameplayCues

	if (HasAuthority())
	{
		UGameplayStatics::ApplyRadialDamage(Cast<UObject>(GetWorld()), 1.f, GetActorLocation(), Radius, UDamageType::StaticClass(), reinterpret_cast<TArray<AActor*>&>(ExcludedPlayers), this, GetInstigatorController(), true, ECollisionChannel::ECC_Visibility);
		
		OnImpact();
	}

	Destroy();
}

void AAbilityActorProjectileAOE::PlayerCollision(AActor * OtherActor)
{
	WorldCollision();
}
