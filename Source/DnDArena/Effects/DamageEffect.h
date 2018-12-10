// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "DamageCalculation.h"
#include "DamageEffect.generated.h"

/**
 * 
 */
UCLASS()
class DNDARENA_API UDamageEffect : public UGameplayEffect
{
	GENERATED_BODY()
	
public:
	UDamageEffect()
	{
		FGameplayEffectExecutionDefinition DamageCalculationDefinition;
		DamageCalculationDefinition.CalculationClass = UDamageCalculation::StaticClass();
		Executions.Add(DamageCalculationDefinition);
	}	
};
