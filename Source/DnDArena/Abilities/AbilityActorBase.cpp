// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "AbilityActorBase.h"
#include "Effects/DamageContext.h"
#include "Engine/World.h"
#include "Gamestates/VersusGamestate.h"
#include "Player/PlayerCharacter.h"

// Sets default values
AAbilityActorBase::AAbilityActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);

	DefaultScene = CreateDefaultSubobject<USceneComponent>(FName("DefaultScene"));
	RootComponent = DefaultScene;
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

void AAbilityActorBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BuildExclusionList();
}

void AAbilityActorBase::AddDamageContext(AActor * Instigator, AActor * DamageCauser, float FireDamage, float FrostDamage, float LightningDamage, float PhysicalDamage, float PoisonDamage, float DarkDamage)
{
	DamageContextHandle = FGameplayEffectContextHandle(new FDamageContext(Instigator, DamageCauser, FireDamage, FrostDamage, LightningDamage, PhysicalDamage, PoisonDamage, DarkDamage));
}

FGameplayEffectContextHandle AAbilityActorBase::GetDamageContextHandle()
{
	return DamageContextHandle;
}

TArray<TSubclassOf<UGameplayEffect>> AAbilityActorBase::GetEffects()
{
	return Effects;
}

void AAbilityActorBase::Activate()
{
}

void AAbilityActorBase::BuildExclusionList()
{
	if (Instigator) 
	{
		ExcludedPlayers = GetWorld()->GetGameState<AVersusGamestate>()->GetTeam(Cast<APlayerCharacter>(Instigator));
	}	
}

