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
	bool bRepeat = true;

	UFUNCTION()
		void CancelRepeat();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AbilityAnimation;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void ActivationLoop();

	UFUNCTION()
		virtual void AbilityComplete();

	UFUNCTION()
		virtual void RepeatExecution();

	UPROPERTY()
		class UAbilityTask_PlayMontageAndWait* MontageTask;

	UPROPERTY()
		class UAbilityTask_WaitGameplayEvent* ExecutionEvent;

	UPROPERTY()
		class UAbilityTask_WaitGameplayEvent* RepeatEvent;

	UPROPERTY()
		class UAbilityTask_WaitInputRelease* InputReleaseTask;
};
