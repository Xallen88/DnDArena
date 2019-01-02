// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "VersusGamestate.generated.h"

/**
 * 
 */
UCLASS()
class DNDARENA_API AVersusGamestate : public AGameState
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Replicated)
	TArray<class APlayerCharacter*> RedTeam;

	UPROPERTY(Replicated)
	TArray<class APlayerCharacter*> BlueTeam;
	

public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	TArray<class APlayerCharacter*> GetTeam (class APlayerCharacter* Player);

	TArray<class APlayerCharacter*> GetTeam(bool bRedTeam);

	UFUNCTION(BlueprintCallable)
	void AddTeammate (class APlayerCharacter* Player, bool bRedTeam);
	
};
