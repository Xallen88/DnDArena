// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "AbilityActorBase.h"


// Sets default values
AAbilityActorBase::AAbilityActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAbilityActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAbilityActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

