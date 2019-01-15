// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "AbilityActorArea.h"
#include "Engine/World.h"
#include "Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"


void AAbilityActorArea::Activate()
{
	// TODO: GameplayCues

	UGameplayStatics::ApplyRadialDamage(Cast<UObject>(GetWorld()), 1.f, GetActorLocation(), Radius, UDamageType::StaticClass(), reinterpret_cast<TArray<AActor*>&>(ExcludedPlayers), this, GetInstigatorController(), true, ECollisionChannel::ECC_Visibility);
}
