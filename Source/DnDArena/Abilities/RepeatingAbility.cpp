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
	UE_LOG(LogTemp, Warning, TEXT("RELEASED"));
}

void URepeatingAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	UE_LOG(LogTemp, Warning, TEXT("BEGIN"));

	// Input release task - Test for release of skill button during animation
	UAbilityTask_WaitInputRelease* InputRelease = UAbilityTask_WaitInputRelease::WaitInputRelease(this, true);
	
	TScriptDelegate<FWeakObjectPtr> InputReleaseScriptDelegate;
	InputReleaseScriptDelegate.BindUFunction(this, FName("CancelRepeat"));
	FInputReleaseDelegate InputReleaseDelagate;
	InputReleaseDelagate.Add(InputReleaseScriptDelegate);
	InputRelease->OnRelease = InputReleaseDelagate;
	InputRelease->Activate();

	// Gameplay event tasks - Waiting for specific tags from animation notify
	UAbilityTask_WaitGameplayEvent* ExecutionEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, FGameplayTag::RequestGameplayTag(FName("Ability.Event.Execute")));

	TScriptDelegate<FWeakObjectPtr> ExecutionScriptDelegate;
	ExecutionScriptDelegate.BindUFunction(this, FName("ExecutionLogic"));
	FWaitGameplayEventDelegate ExecutionDelegate;
	ExecutionDelegate.Add(ExecutionScriptDelegate);
	ExecutionEvent->EventReceived = ExecutionDelegate;
	ExecutionEvent->Activate();

	UAbilityTask_WaitGameplayEvent* RepeatEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, FGameplayTag::RequestGameplayTag(FName("Ability.Event.Repeat")));


	// Activation logic
	ActivationLoop();	
}

void URepeatingAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	UE_LOG(LogTemp, Warning, TEXT("ENDED"));
}

void URepeatingAbility::ActivationLoop()
{
	UE_LOG(LogTemp, Warning, TEXT("ACTIVATION LOOP"));
	if (CommitAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo()))
	{
		UE_LOG(LogTemp, Warning, TEXT("COMMITTED"));
		UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, FName("MontageTask"), AbilityAnimation, 1.0);
		
		TScriptDelegate<FWeakObjectPtr> MontageEndScriptDelegate;
		MontageEndScriptDelegate.BindUFunction(this, FName("AbilityComplete"));
		FMontageWaitSimpleDelegate MontageEndDelegate;
		MontageEndDelegate.Add(MontageEndScriptDelegate);

		MontageTask->OnCompleted = MontageEndDelegate;
		
		MontageTask->Activate();
	}
	else
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false);
	}
}

void URepeatingAbility::AbilityComplete()
{
	if (bRepeat == true)
	{
		ActivationLoop();
	}
	else
	{
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
	}
}
