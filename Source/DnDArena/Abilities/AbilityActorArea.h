// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AbilityActorBase.h"
#include "TargetArea.h"
#include "Color.h"
#include "AbilityActorArea.generated.h"

/**
 * 
 */
UCLASS()
class DNDARENA_API AAbilityActorArea : public AAbilityActorBase
{
	GENERATED_BODY()
	
private:
	FLinearColor ColourSwitch ();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Area, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ATargetArea> TargetArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Area, meta = (AllowPrivateAccess = "true"))
	float Radius;


	
};
