// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "UnrealNetwork.h"

void UPlayerAttributeSet::OnRep_Resource()
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Resource);
}

void UPlayerAttributeSet::SetInitValue(FGameplayAttributeData & AttributeData, float InitValue)
{
	AttributeData.SetBaseValue(InitValue);
	AttributeData.SetCurrentValue(InitValue);
}

void UPlayerAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);	

	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Resource, COND_None, REPNOTIFY_Always);
}


