// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "DamageContext.generated.h"

USTRUCT()
struct DNDARENA_API FDamageContext : public FGameplayEffectContext
{
	GENERATED_USTRUCT_BODY()

public:
	FDamageContext()
	{
	}

	FDamageContext(AActor* Instigator, AActor* DamageCauser, float FireDamage, float FrostDamage, float LightningDamage, float PhysicalDamage, float PoisonDamage, float DarkDamage)
		: FGameplayEffectContext(Instigator, DamageCauser)
	{
		DamageMatrix.Add(FireDamage);
		DamageMatrix.Add(FrostDamage);
		DamageMatrix.Add(LightningDamage);
		DamageMatrix.Add(PhysicalDamage);
		DamageMatrix.Add(PoisonDamage);
		DamageMatrix.Add(DarkDamage);
	}

	~FDamageContext()
	{
	}

	TArray<float> GetDamageMatrix()
	{
		return DamageMatrix;
	}

private:
	TArray<float> DamageMatrix;

};
