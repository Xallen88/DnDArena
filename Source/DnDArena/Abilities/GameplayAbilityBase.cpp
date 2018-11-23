// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityActorBase.h"
#include "GameplayAbilityBase.h"

void UGameplayAbilityBase::ExecutionLogic()
{		
	if (DoesAbilityTagsContain(FGameplayTag::RequestGameplayTag(FName("Ability.Projectile"))))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *GetAbilityActorSpawnLocation().ToString());
		SpawnProjectile();
	}
}

void UGameplayAbilityBase::SpawnProjectile_Implementation()
{
	UClass* ClassName = AbilityActor->GeneratedClass;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AAbilityActorBase>(ClassName, GetAbilityActorSpawnLocation(), GetAbilityActorSpawnRotation(), SpawnParams);
}

bool UGameplayAbilityBase::SpawnProjectile_Validate()
{
	return true;
}

FVector UGameplayAbilityBase::GetAbilityActorSpawnLocation()
{
	return GetAvatarActorFromActorInfo()->GetActorLocation();
}

FRotator UGameplayAbilityBase::GetAbilityActorSpawnRotation()
{
	return GetAvatarActorFromActorInfo()->GetActorRotation();
}

bool UGameplayAbilityBase::DoesAbilityTagsContain(FGameplayTag Tag) const
{
	return AbilityTags.HasTag(Tag);
}
