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
		DamageMatrix.Add(FString("Fire"), FireDamage);
		DamageMatrix.Add(FString("Frost"), FrostDamage);
		DamageMatrix.Add(FString("Lightning"), LightningDamage);
		DamageMatrix.Add(FString("Physical"), PhysicalDamage);
		DamageMatrix.Add(FString("Poison"), PoisonDamage);
		DamageMatrix.Add(FString("Dark"), DarkDamage);
	}

	~FDamageContext()
	{
	}

	TMap<FString, float> GetDamageMatrix()
	{
		return DamageMatrix;
	}

private:
	TMap<FString, float> DamageMatrix;

};
