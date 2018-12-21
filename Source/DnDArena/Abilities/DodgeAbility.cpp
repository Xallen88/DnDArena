// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "DodgeAbility.h"
#include "AbilityTask_PlayMontageAndWait.h"
#include "AbilityTask_WaitInputPress.h"
#include "AbilityTask_WaitDelay.h"
#include "AbilitySystemComponent.h"
#include "Player/PlayerCharacter.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "AbilityTask_ApplyRootMotionConstantForce.h"

void UDodgeAbility::WaitTimeout()
{
	UE_LOG(LogTemp, Warning, TEXT("Timeout"));
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);	
}

void UDodgeAbility::DodgeComplete()
{
	UE_LOG(LogTemp, Warning, TEXT("Complete"));
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}

void UDodgeAbility::ExecutionLogic()
{
	if (CommitAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo()))
	{
		TimeoutTask->EndTask();

		// After successful activation, should apply special cancel and blocks (block all abilities & cancel current ones)
		GetAbilitySystemComponentFromActorInfo()->ApplyAbilityBlockAndCancelTags(AbilityTags, this, true, TagsToBlockDuringExecution, true, TagsToCancelDuringExecution);

		DodgingMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, DodgeAnimation);

		TScriptDelegate<FWeakObjectPtr> DodgingMontageScriptDelegate;
		DodgingMontageScriptDelegate.BindUFunction(this, FName("DodgeComplete"));
		FMontageWaitSimpleDelegate DodgingMontagetDelagate;
		DodgingMontagetDelagate.Add(DodgingMontageScriptDelegate);
		DodgingMontageTask->OnCompleted = DodgingMontagetDelagate;
		DodgingMontageTask->Activate();

		FVector MovementDirection = FVector(1.f, 0.f, 0.f);
		if (GetCurrentAbilitySpec()->InputID == static_cast<int>(AbilityInput::DodgeLeft))
		{
			MovementDirection = GetAvatarActorFromActorInfo()->GetActorRightVector() * -1.f;
		}
		else if (GetCurrentAbilitySpec()->InputID == static_cast<int>(AbilityInput::DodgeRight))
		{
			MovementDirection = GetAvatarActorFromActorInfo()->GetActorRightVector();
		}
		else if (GetCurrentAbilitySpec()->InputID == static_cast<int>(AbilityInput::DodgeForward))
		{
			MovementDirection = GetAvatarActorFromActorInfo()->GetActorForwardVector();
		}
		else if (GetCurrentAbilitySpec()->InputID == static_cast<int>(AbilityInput::DodgeBackward))
		{
			MovementDirection = GetAvatarActorFromActorInfo()->GetActorForwardVector() * -1.f;
		}
		
		// Actual dodge movement
		MovementTask = UAbilityTask_ApplyRootMotionConstantForce::ApplyRootMotionConstantForce(this, NAME_None, MovementDirection, MovementStrength, MovementDuration, true, MovementStrengthCurve, ERootMotionFinishVelocityMode::ClampVelocity, FVector(0.f, 0.f, 0.f), 0.f);
	}
	else
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}
}

void UDodgeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	TimeoutTask = UAbilityTask_WaitDelay::WaitDelay(this, 0.3);

	TScriptDelegate<FWeakObjectPtr> TimeoutScriptDelegate;
	TimeoutScriptDelegate.BindUFunction(this, FName("WaitTimeout"));
	FWaitDelayDelegate TimeoutDelagate;
	TimeoutDelagate.Add(TimeoutScriptDelegate);
	TimeoutTask->OnFinish = TimeoutDelagate;
	TimeoutTask->Activate();

	DoubleTapWaitTask = UAbilityTask_WaitInputPress::WaitInputPress(this, false);

	TScriptDelegate<FWeakObjectPtr> DoubleTapWaitScriptDelegate;
	DoubleTapWaitScriptDelegate.BindUFunction(this, FName("ExecutionLogic"));
	FInputPressDelegate DoubleTapWaitDelagate;
	DoubleTapWaitDelagate.Add(DoubleTapWaitScriptDelegate);
	DoubleTapWaitTask->OnPress = DoubleTapWaitDelagate;
	DoubleTapWaitTask->Activate();
}

void UDodgeAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	GetAbilitySystemComponentFromActorInfo()->UnBlockAbilitiesWithTags(TagsToBlockDuringExecution);

	if (TimeoutTask)
	{
		TimeoutTask->EndTask();
	}
	if (DoubleTapWaitTask)
	{
		DoubleTapWaitTask->EndTask();
	}
	if (DodgingMontageTask)
	{
		DodgingMontageTask->EndTask();
	}
	if (MovementTask)
	{
		MovementTask->EndTask();
	}
}
