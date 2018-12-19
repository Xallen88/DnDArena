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
		FGameplayTagContainer TagsToCancel;
		TagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Skill")));		
		TagsToBlock.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));
		GetAbilitySystemComponentFromActorInfo()->ApplyAbilityBlockAndCancelTags(AbilityTags, this, true, TagsToBlock, true, TagsToCancel);

		DodgingMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, DodgeAnimation);

		TScriptDelegate<FWeakObjectPtr> DodgingMontageScriptDelegate;
		DodgingMontageScriptDelegate.BindUFunction(this, FName("DodgeComplete"));
		FMontageWaitSimpleDelegate DodgingMontagetDelagate;
		DodgingMontagetDelagate.Add(DodgingMontageScriptDelegate);
		DodgingMontageTask->OnCompleted = DodgingMontagetDelagate;
		DodgingMontageTask->Activate();

		Cast<APlayerCharacter>(GetAvatarActorFromActorInfo())->GetCharacterMovement()->AddForce(FVector(300000000.f, 0.f, 0.f));

		// Start dodge charge regen
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

	GetAbilitySystemComponentFromActorInfo()->UnBlockAbilitiesWithTags(TagsToBlock);

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
}
