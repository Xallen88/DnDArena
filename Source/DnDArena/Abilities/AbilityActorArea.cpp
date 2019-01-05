// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "AbilityActorArea.h"
#include "Gamestates/VersusGamestate.h"
#include "Engine/World.h"
#include "Player/PlayerCharacter.h"


FLinearColor AAbilityActorArea::ColourSwitch()
{
	if (HasAuthority())
	{
		return FLinearColor(); // Colour doesn't matter on Server
	}

	if (GetWorld()->GetGameState<AVersusGamestate>()->GetTeam(Cast<APlayerCharacter>(Instigator)).Contains(Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn())))
	{
		return FLinearColor(0.f, 1.f, 0.f);
	}
	
	return FLinearColor(1.f, 0.f, 0.f);
}


