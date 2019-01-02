// Fill out your copyright notice in the Description page of Project Settings.

#include "ControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "Gamemodes/VersusGamemode.h"

//void AControllerBase::BeginPlay()
//{
//	if (HasAuthority())
//	{
//		Cast<AVersusGamemode>(UGameplayStatics::GetGameMode(GetWorld()))->SpawnCharacterTemp(this);
//		
//	}
//}

UPlayerHUD * AControllerBase::GetPlayerHUD()
{
	return PlayerHUD;
}

void AControllerBase::SetPlayerHUD(UPlayerHUD* PHUD)
{
	PlayerHUD = PHUD;
}

