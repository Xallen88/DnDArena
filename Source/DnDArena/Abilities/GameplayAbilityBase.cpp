// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayAbilityBase.h"
#include "AbilityActorBase.h"
#include "AbilityTask_SpawnActor.h"
#include "Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"

void UGameplayAbilityBase::ApplyMovementEffect()
{
	if (DoesAbilityTagsContain(FGameplayTag::RequestGameplayTag(FName("Ability.Movement.Root"))))
	{
		// Apply ability root GameplayEffect
	}
	if (DoesAbilityTagsContain(FGameplayTag::RequestGameplayTag(FName("Ability.Movement.Slow"))))
	{
		// Apply ability slow GameplayEffect
	}
}

void UGameplayAbilityBase::RemoveMovementEffect()
{
	// Remove ability root GameplayEffect
	// Remove ability slow GameplayEffect
}

void UGameplayAbilityBase::ExecutionLogic()
{		
	if (DoesAbilityTagsContain(FGameplayTag::RequestGameplayTag(FName("Ability.Projectile"))))
	{ 		
		ProjectileExecution();
	}
}

void UGameplayAbilityBase::ProjectileExecution()
{	
	SpawnAbilityActor();
}

bool UGameplayAbilityBase::SpawnAbilityActor()
{
	if (GetCurrentActorInfo()->IsNetAuthority())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = Cast<APawn>(GetAvatarActorFromActorInfo());
		AbilityActor = GetWorld()->SpawnActor<AAbilityActorBase>(AbilityActorClass, GetAbilityActorSpawnLocation(), GetAbilityActorSpawnRotation(), SpawnParams);
		if (AbilityActor)
		{
			AbilityActor->AddDamageContext(SpawnParams.Instigator, AbilityActor, FireDamage, FrostDamage, LightningDamage, PhysicalDamage, PoisonDamage, DarkDamage);
			return true;
		}
	}
	return false;
}

FVector UGameplayAbilityBase::GetAbilityActorSpawnLocation()
{
	return GetAvatarActorFromActorInfo()->GetActorLocation();
}

FRotator UGameplayAbilityBase::GetAbilityActorSpawnRotation()
{	
	if (DoesAbilityTagsContain(FGameplayTag::RequestGameplayTag(FName("Ability.Rotation.UseCamera"))))
	{
		return Cast<APlayerCharacter>(GetAvatarActorFromActorInfo())->GetCameraComponent()->GetComponentRotation();
	}
	else
	{
		return GetAvatarActorFromActorInfo()->GetActorRotation();
	}
	
}

bool UGameplayAbilityBase::DoesAbilityTagsContain(FGameplayTag Tag) const
{
	return AbilityTags.HasTag(Tag);
}
