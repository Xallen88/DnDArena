// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "VersusGamemode.h"
#include "Engine/World.h"
#include "Player/PlayerCharacter.h"
#include "Player/ControllerBase.h"
#include "Gamestates/VersusGamestate.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/HUD.h"




AVersusGamemode::AVersusGamemode()
{	
	GameSessionClass = AGameSession::StaticClass();
	GameStateClass = AVersusGamestate::StaticClass();
	PlayerControllerClass = AControllerBase::StaticClass();
	PlayerStateClass = APlayerState::StaticClass();
	HUDClass = AHUD::StaticClass();
	DefaultPawnClass = APlayerCharacter::StaticClass();
	//SpectatorClass = ;
	//ReplaySpectatorPlayerControllerClass = ;
	//ServerStatReplicatorClass = ;
}

void AVersusGamemode::SpawnCharacterTemp(class AControllerBase* Controller)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	APlayerCharacter* Player = GetWorld()->SpawnActor<APlayerCharacter>(DefaultPawnClass, FindPlayerStart(Controller)->GetActorTransform().GetLocation(), FRotator(), SpawnParams);
	
	Controller->Possess(Player);

	GetGameState<AVersusGamestate>()->AddTeammate(Player, (LoadedControllers % 2 ? false : true));

	++LoadedControllers;
}

