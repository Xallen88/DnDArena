// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "AbilityActorBase.h"
#include "Effects/DamageContext.h"


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

void AAbilityActorBase::AddDamageContext(AActor * Instigator, AActor * DamageCauser, float FireDamage, float FrostDamage, float LightningDamage, float PhysicalDamage, float PoisonDamage, float DarkDamage)
{
	DamageContextHandle = FGameplayEffectContextHandle(new FDamageContext(Instigator, DamageCauser, FireDamage, FrostDamage, LightningDamage, PhysicalDamage, PoisonDamage, DarkDamage));
}

FGameplayEffectContextHandle AAbilityActorBase::GetDamageContextHandle()
{
	return DamageContextHandle;
}

