// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectUIData.h"
#include "SlateBrush.h"
#include "GameplayEffectUIDataBasic.generated.h"

/**
 * 
 */
UCLASS()
class DNDARENA_API UGameplayEffectUIDataBasic : public UGameplayEffectUIData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Data, meta = (MultiLine = "true"))
	FSlateBrush EffectIcon;
	
	
};
