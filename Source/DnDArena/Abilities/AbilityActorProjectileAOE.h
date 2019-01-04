// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AbilityActorProjectile.h"
#include "AbilityActorProjectileAOE.generated.h"

/**
 * 
 */
UCLASS()
class DNDARENA_API AAbilityActorProjectileAOE : public AAbilityActorProjectile
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float Radius;

	virtual void WorldCollision() override;

	virtual void PlayerCollision(AActor* OtherActor) override;
	
	
};
