// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "BuffBarExecution.generated.h"

/**
 * 
 */
UCLASS()
class DNDARENA_API UBuffBarExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
	
};
