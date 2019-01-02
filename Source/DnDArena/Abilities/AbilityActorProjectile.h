// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AbilityActorBase.h"
#include "AbilityActorProjectile.generated.h"

/**
 * 
 */
UCLASS()
class DNDARENA_API AAbilityActorProjectile : public AAbilityActorBase
{
	GENERATED_BODY()
	
public:
	AAbilityActorProjectile();

protected:
	class USphereComponent* CollisionSphere;

	class UStaticMeshComponent* StaticMesh;

	class UProjectileMovementComponent* MovementComponent;

public:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	
};
