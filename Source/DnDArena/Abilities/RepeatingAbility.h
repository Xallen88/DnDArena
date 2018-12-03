// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityBase.h"
#include "RepeatingAbility.generated.h"

/**
 * 
 */
UCLASS()
class DNDARENA_API URepeatingAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()

private:
	bool bRepeat = false;

	UFUNCTION()
	void CancelRepeat();

	UFUNCTION()
	void SetRepeat();
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
