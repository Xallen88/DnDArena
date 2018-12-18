// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "UnrealNetwork.h"
#include "Player/PlayerCharacter.h"

void UPlayerAttributeSet::OnRep_Health()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Health);
}

void UPlayerAttributeSet::OnRep_MaxHealth()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, MaxHealth);
}

void UPlayerAttributeSet::OnRep_Resource()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Resource);
}

void UPlayerAttributeSet::OnRep_MaxResource()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, MaxResource);
}

void UPlayerAttributeSet::OnRep_AttackSpeed()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, AttackSpeed);
}

void UPlayerAttributeSet::OnRep_CastSpeed()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, CastSpeed);
}

void UPlayerAttributeSet::OnRep_MovementSpeed()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, MovementSpeed);

	Cast<APlayerCharacter>(GetOwningAbilitySystemComponent()->GetAvatarActor())->UpdateMovement();
}

void UPlayerAttributeSet::SetInitValue(FGameplayAttributeData & AttributeData, float InitValue)
{
	AttributeData.SetBaseValue(InitValue);
	AttributeData.SetCurrentValue(InitValue);
}

void UPlayerAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);	

	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Resource, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, MaxResource, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, CastSpeed, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
}


