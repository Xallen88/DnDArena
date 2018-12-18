// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "StandardAbility.h"
#include "AbilityTask_PlayMontageAndWait.h"
#include "AbilityTask_WaitCancel.h"
#include "AbilityTask_WaitConfirmCancel.h"
#include "AbilityTask_WaitGameplayEvent.h"
#include "AbilityTask.h"
#include "GameplayTask.h"

void UStandardAbility::ActivateByInput()
{
	ReadyMontageTask->EndTask();
	ExecutionMontageTask->Activate();
}	

void UStandardAbility::AbilityComplete()
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}

void UStandardAbility::CancelByInput()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UStandardAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	// Casting
	if (DoesAbilityTagsContain(FGameplayTag::RequestGameplayTag(FName("Ability.Casted"))) && CastingAnimation)
	{
		CastingMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, CastingAnimation, 1.0);

		TScriptDelegate<FWeakObjectPtr> MontageEndScriptDelegate;
		MontageEndScriptDelegate.BindUFunction(this, FName("AbilityReady"));
		FMontageWaitSimpleDelegate MontageEndDelegate;
		MontageEndDelegate.Add(MontageEndScriptDelegate);
		CastingMontageTask->OnCompleted = MontageEndDelegate;
		CastingMontageTask->OnBlendOut = MontageEndDelegate;
	}

	// Ready
	if (DoesAbilityTagsContain(FGameplayTag::RequestGameplayTag(FName("Ability.Readied"))) && ReadyAnimation)
	{
		ReadyMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, ReadyAnimation, 1.0);
	}

	// Execution
	ExecutionMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, ExecutionAnimation, 1.0);

	TScriptDelegate<FWeakObjectPtr> ExecutionMontageEndScriptDelegate;
	ExecutionMontageEndScriptDelegate.BindUFunction(this, FName("AbilityComplete"));
	FMontageWaitSimpleDelegate ExecutionMontageEndDelegate;
	ExecutionMontageEndDelegate.Add(ExecutionMontageEndScriptDelegate);
	ExecutionMontageTask->OnCompleted = ExecutionMontageEndDelegate;
	ExecutionMontageTask->OnBlendOut = ExecutionMontageEndDelegate;


	ExecutionEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, FGameplayTag::RequestGameplayTag(FName("Ability.Event.Execute")));

	TScriptDelegate<FWeakObjectPtr> ExecutionScriptDelegate;
	ExecutionScriptDelegate.BindUFunction(this, FName("ExecutionLogic"));
	FWaitGameplayEventDelegate ExecutionDelegate;
	ExecutionDelegate.Add(ExecutionScriptDelegate);
	ExecutionEvent->EventReceived = ExecutionDelegate;
	ExecutionEvent->Activate();

	// Cancel & confirm inputs
	if (ReadyMontageTask || CastingMontageTask)
	{
		CancelInputTask = UAbilityTask_WaitCancel::WaitCancel(this);

		TScriptDelegate<FWeakObjectPtr> CancelScriptDelegate;
		CancelScriptDelegate.BindUFunction(this, FName("CancelByInput"));
		FWaitCancelDelegate CancelDelegate;
		CancelDelegate.Add(CancelScriptDelegate);
		CancelInputTask->OnCancel = CancelDelegate;
		CancelInputTask->Activate();
	}
	if (ReadyMontageTask)
	{
		ConfirmInputTask = UAbilityTask_WaitConfirmCancel::WaitConfirmCancel(this);

		TScriptDelegate<FWeakObjectPtr> ConfirmScriptDelegate;
		ConfirmScriptDelegate.BindUFunction(this, FName("ActivateByInput"));
		FWaitConfirmCancelDelegate ConfirmDelegate;
		ConfirmDelegate.Add(ConfirmScriptDelegate);
		ConfirmInputTask->OnConfirm = ConfirmDelegate;
	}

	// Activate
	if (CommitAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo())) 
	{
		if (CastingMontageTask)
		{
			CastingMontageTask->Activate();
		}
		else if (ReadyMontageTask)
		{
			ReadyMontageTask->Activate();
			ConfirmInputTask->Activate();
		}
		else
		{
			ExecutionMontageTask->Activate();
		}
	}
	else
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}
}

void UStandardAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (CastingMontageTask)
	{
		CastingMontageTask->EndTask();
	}
	if (ReadyMontageTask)
	{
		ReadyMontageTask->EndTask();
	}
	if (CancelInputTask)
	{
		CancelInputTask->EndTask();
	}
	if (ConfirmInputTask)
	{
		ConfirmInputTask->EndTask();
	}
	ExecutionEvent->EndTask();
	ExecutionMontageTask->EndTask();
}

void UStandardAbility::AbilityReady()
{
	if (ReadyMontageTask)
	{
		ReadyMontageTask->Activate();
		ConfirmInputTask->Activate();		
	}
	else
	{
		ExecutionMontageTask->Activate();
		CancelInputTask->EndTask();		
	}
}
