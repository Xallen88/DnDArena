// Fill out your copyright notice in the Description page of Project Settings.

#include "ControllerBase.h"

UPlayerHUD * AControllerBase::GetPlayerHUD()
{
	return PlayerHUD;
}

void AControllerBase::SetPlayerHUD(UPlayerHUD* PHUD)
{
	PlayerHUD = PHUD;
}

void AControllerBase::AddBuffToHUD(FActiveGameplayEffectHandle EffectHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("ADD BUFF TO HUD"));
}
