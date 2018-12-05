// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "RepeatingAbility.h"
#include "AbilityTask.h"
#include "AbilityTask_WaitInputPress.h"
#include "AbilityTask_WaitInputRelease.h"
#include "AbilityTask_WaitGameplayEvent.h"
#include "AbilityTask_PlayMontageAndWait.h"

void URepeatingAbility::CancelRepeat()
{
	bRepeat = false;
}

void URepeatingAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	UE_LOG(LogTemp, Warning, TEXT("BEGIN"));
	bRepeat = true;

	// Input release task - Test for release of skill button during animation
	UAbilityTask_WaitInputRelease* InputRelease = UAbilityTask_WaitInputRelease::WaitInputRelease(this, true);
	
	TScriptDelegate<FWeakObjectPtr> InputReleaseScriptDelegate;
	InputReleaseScriptDelegate.BindUFunction(this, FName("CancelRepeat"));
	FInputReleaseDelegate InputReleaseDelagate;
	InputReleaseDelagate.Add(InputReleaseScriptDelegate);
	InputRelease->OnRelease = InputReleaseDelagate;
	InputRelease->Activate();

	// Gameplay event tasks - Waiting for specific tags from animation notify (Execute & Repeat)
	ExecutionEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, FGameplayTag::RequestGameplayTag(FName("Ability.Event.Execute")));

	TScriptDelegate<FWeakObjectPtr> ExecutionScriptDelegate;
	ExecutionScriptDelegate.BindUFunction(this, FName("ExecutionLogic"));
	FWaitGameplayEventDelegate ExecutionDelegate;
	ExecutionDelegate.Add(ExecutionScriptDelegate);
	ExecutionEvent->EventReceived = ExecutionDelegate;
	ExecutionEvent->Activate();

	UAbilityTask_WaitGameplayEvent* RepeatEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, FGameplayTag::RequestGameplayTag(FName("Ability.Event.Repeat")));

	TScriptDelegate<FWeakObjectPtr> RepeatScriptDelegate;
	RepeatScriptDelegate.BindUFunction(this, FName("RepeatExecution"));
	FWaitGameplayEventDelegate RepeatDelegate;
	RepeatDelegate.Add(RepeatScriptDelegate);
	RepeatEvent->EventReceived = RepeatDelegate;
	RepeatEvent->Activate();	

	// Activation logic
	ActivationLoop();	
}

void URepeatingAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	ExecutionEvent->EndTask();
	UE_LOG(LogTemp, Warning, TEXT("ENDED"));
}

void URepeatingAbility::ActivationLoop()
{
	if (CommitAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo()))
	{
		// Montage task
		MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AbilityAnimation, 1.0);

		TScriptDelegate<FWeakObjectPtr> MontageEndScriptDelegate;
		MontageEndScriptDelegate.BindUFunction(this, FName("AbilityComplete"));
		FMontageWaitSimpleDelegate MontageEndDelegate;
		MontageEndDelegate.Add(MontageEndScriptDelegate);
		MontageTask->OnCompleted = MontageEndDelegate;
		MontageTask->OnBlendOut = MontageEndDelegate;
		
		MontageTask->Activate();
	}
	else
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false);
	}
}

void URepeatingAbility::AbilityComplete()
{
	if (bRepeat)
	{
		ActivationLoop();
	}
	else
	{
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
	}
}

void URepeatingAbility::RepeatExecution()
{
	if (bRepeat)
	{
		ExecutionLogic();
	}
	else
	{
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
	}
}
