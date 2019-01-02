// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "VersusGamemode.generated.h"

/**
 * 
 */
UCLASS()
class DNDARENA_API AVersusGamemode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AVersusGamemode();

protected:	
	int8 LoadedControllers = 0;


public:	
	UFUNCTION(BlueprintCallable)
	void SpawnCharacterTemp(class AControllerBase* Controller);
};
