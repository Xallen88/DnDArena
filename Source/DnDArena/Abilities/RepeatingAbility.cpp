// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "RepeatingAbility.h"
#include "AbilityTask.h"
#include "AbilityTask_WaitInputPress.h"
#include "AbilityTask_WaitInputRelease.h"

void URepeatingAbility::CancelRepeat()
{
	bRepeat = false;
}

void URepeatingAbility::SetRepeat()
{
	bRepeat = true;
	UE_LOG(LogTemp, Warning, TEXT("PRESSED"));
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void URepeatingAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	UE_LOG(LogTemp, Warning, TEXT("BEGIN"));
	UAbilityTask_WaitInputPress* InputPress = UAbilityTask::NewAbilityTask<UAbilityTask_WaitInputPress>(this, FName("InputPressTask"));	

	TScriptDelegate<FWeakObjectPtr> ScriptDelegate;
	ScriptDelegate.BindUFunction(this, FName("URepeatingAbility::SetRepeat"));

	FInputPressDelegate InputPressDelegate;
	InputPressDelegate.Add(ScriptDelegate);

	InputPress->OnPress = InputPressDelegate;
	
}

void URepeatingAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
