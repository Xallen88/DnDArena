// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/AbilityActorArea.h"
#include "AbilityActorAreaTick.generated.h"

/**
 * 
 */
UCLASS()
class DNDARENA_API AAbilityActorAreaTick : public AAbilityActorArea
{
	GENERATED_BODY()
	
private:
	FTimerHandle AreaTickTimerHandle;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AreaTick, meta = (AllowPrivateAccess = "true"))
	int32 AreaTicks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AreaTick, meta = (AllowPrivateAccess = "true"))
	float AreaTickInterval;
	
	void AreaTickHelper ();

	virtual void AreaTick ();

public:
	virtual void Activate () override;
	
};
