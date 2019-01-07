// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "AbilityActorAreaTick.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"


void AAbilityActorAreaTick::AreaTickHelper()
{
	if (--AreaTicks <= 0)
	{
		GetWorldTimerManager().ClearTimer(AreaTickTimerHandle);
		SetLifeSpan(1.f);
	}
	
	AreaTick();
}

void AAbilityActorAreaTick::AreaTick()
{
	UGameplayStatics::ApplyRadialDamage(Cast<UObject>(GetWorld()), 1.f, GetActorLocation(), Radius, UDamageType::StaticClass(), reinterpret_cast<TArray<AActor*>&>(ExcludedPlayers), this, GetInstigatorController(), true, ECollisionChannel::ECC_Visibility);
}

void AAbilityActorAreaTick::Activate()
{
	GetWorldTimerManager().SetTimer(AreaTickTimerHandle, this, &AAbilityActorAreaTick::AreaTickHelper, AreaTickInterval, true);
}
