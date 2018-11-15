// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAttributeSet.h"

void UPlayerAttributeSet::SetInitValue(FGameplayAttributeData & AttributeData, float InitValue)
{
	AttributeData.SetBaseValue(InitValue);
	AttributeData.SetCurrentValue(InitValue);
}
