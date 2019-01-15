// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "StandardAbility.h"
#include "AbilityTask_PlayMontageAndWait.h"
#include "AbilityTask_WaitCancel.h"
#include "AbilityTask_WaitConfirmCancel.h"
#include "AbilityTask_WaitGameplayEvent.h"
#include "AbilityTask_Tick.h"
#include "AbilitySystemComponent.h"

void UStandardAbility::ActivateByInput()
{
	ReadyMontageTask->EndTask();
	CommitAbilityCooldown(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false);
	ExecutionMontageTask->Activate();
	if (TargetAreaActor)
	{
		TargetAreaActor->Destroy();
	}
	if (TargetAreaClass && GetCurrentActorInfo()->IsNetAuthority())
	{
		SpawnLocation = TraceTargetLocation();
		SpawnTargetArea_Multicast(Cast<APawn>(GetAvatarActorFromActorInfo()), SpawnLocation);		
	}
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
	// Check cooldown first
	if(CheckCooldown(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo()))
	{	
		// Commit cost, regardless of execution
		if (CommitAbilityCost(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo()))
		{
			// Casting
			if (DoesAbilityTagsContain(FGameplayTag::RequestGameplayTag(FName("Ability.Casted"))) && CastingAnimation)
			{
				CastingMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, CastingAnimation, 1.0);

				TScriptDelegate<FWeakObjectPtr> MontageEndScriptDelegate;
				MontageEndScriptDelegate.BindUFunction(this, FName("AbilityReady"));
				CastingMontageTask->OnCompleted.Add(MontageEndScriptDelegate);
				CastingMontageTask->OnBlendOut.Add(MontageEndScriptDelegate);
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
			ExecutionMontageTask->OnCompleted.Add(ExecutionMontageEndScriptDelegate);
			ExecutionMontageTask->OnBlendOut.Add(ExecutionMontageEndScriptDelegate);


			ExecutionEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, FGameplayTag::RequestGameplayTag(FName("Ability.Event.Execute")));

			TScriptDelegate<FWeakObjectPtr> ExecutionScriptDelegate;
			ExecutionScriptDelegate.BindUFunction(this, FName("ExecutionLogic"));
			ExecutionEvent->EventReceived.Add(ExecutionScriptDelegate);
			ExecutionEvent->Activate();

			// Cancel input
			if (ReadyMontageTask || CastingMontageTask)
			{
				CancelInputTask = UAbilityTask_WaitCancel::WaitCancel(this);

				TScriptDelegate<FWeakObjectPtr> CancelScriptDelegate;
				CancelScriptDelegate.BindUFunction(this, FName("CancelByInput"));
				CancelInputTask->OnCancel.Add(CancelScriptDelegate);
				CancelInputTask->Activate();

				// Target area logic
				if (TargetAreaClass && IsLocallyControlled())
				{
					SpawnTargetArea();
					if (TargetAreaActor)
					{
						TargetAreaActor->Ability = this;
					}
				}
			}

			// Confirm input
			if (ReadyMontageTask)
			{
				ConfirmInputTask = UAbilityTask_WaitConfirmCancel::WaitConfirmCancel(this);

				TScriptDelegate<FWeakObjectPtr> ConfirmScriptDelegate;
				ConfirmScriptDelegate.BindUFunction(this, FName("ActivateByInput"));
				ConfirmInputTask->OnConfirm.Add(ConfirmScriptDelegate);
			}

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
				CommitAbilityCooldown(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false);
				ExecutionMontageTask->Activate();
			}
		}
		else
		{
			CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
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
	if (TargetAreaActor)
	{
		TargetAreaActor->Destroy();
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
		CommitAbilityCooldown(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false);
		ExecutionMontageTask->Activate();
		CancelInputTask->EndTask();		
	}
}

void UStandardAbility::SpawnTargetArea()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = Cast<APawn>(GetAvatarActorFromActorInfo());
	TargetAreaActor = GetWorld()->SpawnActor<ATargetArea>(TargetAreaClass, GetAvatarActorFromActorInfo()->GetActorLocation(), GetAvatarActorFromActorInfo()->GetActorRotation(), SpawnParams);
}

void UStandardAbility::SpawnTargetArea_Multicast_Implementation(APawn* Instigator, FVector Location)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = Instigator;
	ATargetArea* Target = GetWorld()->SpawnActor<ATargetArea>(TargetAreaClass, Location, Instigator->GetActorRotation(), SpawnParams);
	Target->SetActorTickEnabled(false);
	Target->SetLifeSpan(TargetAreaDuration);
}

