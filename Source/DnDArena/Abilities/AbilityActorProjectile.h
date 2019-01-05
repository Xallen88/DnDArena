// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AbilityActorBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
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

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilityActor, meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AbilityActor, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AbilityActor, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* MovementComponent;

	FVector SpawnLocation;

	float ProjectileRange;
	
protected:
	virtual void WorldCollision ();

	virtual void PlayerCollision (AActor* OtherActor);

public:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(NetMulticast, Reliable)
	void SetRange (float AbilityRange);
};
