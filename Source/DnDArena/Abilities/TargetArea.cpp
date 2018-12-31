// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "TargetArea.h"


// Sets default values
ATargetArea::ATargetArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATargetArea::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargetArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Ability && Ability->IsActive())
	{
		SetActorLocation(Ability->TraceTargetLocation());
	}	
}

