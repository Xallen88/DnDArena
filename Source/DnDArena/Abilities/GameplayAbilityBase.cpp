// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayAbilityBase.h"

bool UGameplayAbilityBase::DoesAbilityTagsContain(FGameplayTag Tag) const
{
	return AbilityTags.HasTag(Tag);
}
