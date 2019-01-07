// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AbilityActorAreaTick.h"
#include "AbilityActorAreaTickSpawn.generated.h"

/**
 * 
 */
UCLASS()
class DNDARENA_API AAbilityActorAreaTickSpawn : public AAbilityActorAreaTick
{
	GENERATED_BODY()

private:
	FVector RandomLocationInCircle(float RadiusOffset = 0.f, float z = 0.f);
	
protected:
	virtual void AreaTick () override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AreaTick, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> SpawnableAbilityActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AreaTick, meta = (AllowPrivateAccess = "true"))
	float ZOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AreaTick, meta = (AllowPrivateAccess = "true"))
	float RadiusOffset;
	
	
};
