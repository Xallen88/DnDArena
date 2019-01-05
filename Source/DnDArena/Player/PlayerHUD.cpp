// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHUD.h"

bool UPlayerHUD::IsBuffActive(FActiveGameplayEffectHandle EffectHandle)
{
	return ActiveBuffs.Contains(EffectHandle);
}

bool UPlayerHUD::AddActiveBuff(FActiveGameplayEffectHandle EffectHandle)
{
	if (IsBuffActive(EffectHandle))
	{
		return false;
	}

	return ActiveBuffs.Add(EffectHandle) >= 0;
}

bool UPlayerHUD::RemoveActiveBuff(FActiveGameplayEffectHandle EffectHandle)
{
	if (IsBuffActive(EffectHandle))
	{
		return false;
	}

	return ActiveBuffs.Remove(EffectHandle) > 0;
}
