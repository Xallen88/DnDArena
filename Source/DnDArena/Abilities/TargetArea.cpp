// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "TargetArea.h"
#include "Gamestates/VersusGamestate.h"
#include "Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Classes/Materials/Material.h"
#include "Classes/Materials/MaterialInstanceDynamic.h"


// Sets default values
ATargetArea::ATargetArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Decal = CreateDefaultSubobject<UDecalComponent>(FName("Decal"));
	Decal->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATargetArea::BeginPlay()
{
	Super::BeginPlay();
	
	UMaterialInstanceDynamic* MaterialInstance = Decal->CreateDynamicMaterialInstance();
	MaterialInstance->SetVectorParameterValue(FName("Colour"), ColourSwitch());
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

FLinearColor ATargetArea::ColourSwitch()
{
	if (Ability)
	{
		return FLinearColor(0.f, 0.f, 1.f);
	}
	if (GetWorld()->GetGameState<AVersusGamestate>()->GetTeam(Cast<APlayerCharacter>(Instigator)).Contains(Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn())))
	{
		return FLinearColor(0.f, 1.f, 0.f);
	}
	return FLinearColor(1.f, 0.f, 0.f);
}

