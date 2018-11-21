// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class DNDARENA_API UGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual uint8 GetGameplayTaskDefaultPriority() const override { return FGameplayTasks::DefaultPriority; }
	
	UFUNCTION(BlueprintCallable, Category = Ability)
		bool DoesAbilityTagsContain(FGameplayTag Tag) const;
	
};