// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityBase.h"
#include "TargetArea.h"
#include "StandardAbility.generated.h"

/**
 * 
 */
UCLASS()
class DNDARENA_API UStandardAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void CancelByInput();

	UFUNCTION()
	void ActivateByInput();

	UFUNCTION()
	void AbilityComplete();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* CastingAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* ReadyAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* ExecutionAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Targetting, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ATargetArea> TargetAreaClass;

	UPROPERTY()
	ATargetArea* TargetAreaActor;

	UPROPERTY()
	class UAbilityTask_PlayMontageAndWait* CastingMontageTask;
	UPROPERTY()
	class UAbilityTask_PlayMontageAndWait* ReadyMontageTask;
	UPROPERTY()
	class UAbilityTask_PlayMontageAndWait* ExecutionMontageTask;

	UPROPERTY()
	class UAbilityTask_WaitGameplayEvent* ExecutionEvent;

	UPROPERTY()
	class UAbilityTask_WaitConfirmCancel* ConfirmInputTask;
	UPROPERTY()
	class UAbilityTask_WaitCancel* CancelInputTask;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION()
	virtual void AbilityReady();

	void SpawnTargetArea();

};
