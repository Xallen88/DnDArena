// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "VersusGamestate.h"
#include "UnrealNetwork.h"
#include "Player/PlayerCharacter.h"

void AVersusGamestate::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AVersusGamestate, RedTeam);
	DOREPLIFETIME(AVersusGamestate, BlueTeam);
}

TArray<class APlayerCharacter*> AVersusGamestate::GetTeam(APlayerCharacter * Player)
{
	if (RedTeam.Contains(Player))
	{
		return RedTeam;
	}
	return BlueTeam;
}

TArray<class APlayerCharacter*> AVersusGamestate::GetTeam(bool bRedTeam)
{
	if (bRedTeam)
	{
		return RedTeam;
	}
	return BlueTeam;
}

void AVersusGamestate::AddTeammate(APlayerCharacter* Player, bool bRedTeam)
{
	if (bRedTeam)
	{
		RedTeam.Add(Player);
	}
	else
	{
		BlueTeam.Add(Player);
	}
}
