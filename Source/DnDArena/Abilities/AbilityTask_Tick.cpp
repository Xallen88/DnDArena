// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "AbilityTask_Tick.h"


UAbilityTask_Tick::UAbilityTask_Tick(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bTickingTask = true;
}

UAbilityTask_Tick * UAbilityTask_Tick::AbilityTick(UGameplayAbility* OwningAbility, FName TaskInstanceName)
{
	UAbilityTask_Tick* MyTask = NewAbilityTask<UAbilityTask_Tick>(OwningAbility, TaskInstanceName);
	
	return MyTask;
}

void UAbilityTask_Tick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("TICK"));

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnTick.Broadcast(DeltaTime);
	}
	
}

void UAbilityTask_Tick::OnDestroy(bool AbilityIsEnding)
{
	Super::OnDestroy(AbilityIsEnding);
}
