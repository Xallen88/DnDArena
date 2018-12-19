// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityBase.h"
#include "DodgeAbility.generated.h"

/**
 * 
 */
UCLASS()
class DNDARENA_API UDodgeAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()
	
private:
	UFUNCTION()
		void WaitTimeout();

	UFUNCTION()
		void DodgeComplete();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* DodgeAnimation;
	
	UPROPERTY()
		class UAbilityTask_PlayMontageAndWait* DodgingMontageTask;

	UPROPERTY()
		class UAbilityTask_WaitInputPress* DoubleTapWaitTask;

	UPROPERTY()
		class UAbilityTask_WaitDelay* TimeoutTask;

	virtual void ExecutionLogic() override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

};
