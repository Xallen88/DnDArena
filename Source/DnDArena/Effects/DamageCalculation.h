// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageCalculation.generated.h"

/**
 * 
 */
UCLASS()
class DNDARENA_API UDamageCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_UCLASS_BODY()
		
public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
	
};
