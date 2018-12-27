// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "MovementExecution.h"
#include "AbilitySystemComponent.h"
#include "Player/PlayerCharacter.h"
#include "Gameframework/CharacterMovementComponent.h"

void UMovementExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(ExecutionParams.GetTargetAbilitySystemComponent()->GetAvatarActor());
	if (!Player){ return; }

	Player->UpdateMovement();
}




