// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "AbilityActorAreaTickSpawn.h"


FVector AAbilityActorAreaTickSpawn::RandomLocationInCircle(float RadiusOffset, float z)
{
	float theta = FMath::RandRange(0.f, 2.f * PI);
	float r = FMath::RandRange(0.f, Radius - RadiusOffset);

	float x = FMath::Sin(theta) * r;
	float y = FMath::Cos(theta) * r;

	return FVector(x, y, z) + GetActorLocation();
}

void AAbilityActorAreaTickSpawn::AreaTick()
{
	if (HasAuthority())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = GetInstigator();
		AAbilityActorBase* SpawnedActor = GetWorld()->SpawnActor<AAbilityActorBase>(SpawnableAbilityActor, RandomLocationInCircle(RadiusOffset, ZOffset), GetActorRotation(), SpawnParams);
		if (SpawnedActor)
		{
			SpawnedActor->AddDamageContext(DamageContextHandle);
		}
	}
}

