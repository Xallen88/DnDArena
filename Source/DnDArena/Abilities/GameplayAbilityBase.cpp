// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayAbilityBase.h"
#include "AbilityActorBase.h"
#include "AbilityActorProjectile.h"
#include "AbilityActorArea.h"
#include "Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UGameplayAbilityBase::ApplyMovementEffect()
{
	if (DoesAbilityTagsContain(FGameplayTag::RequestGameplayTag(FName("Ability.Root"))))
	{
		// Apply ability root GameplayEffect
	}
	if (DoesAbilityTagsContain(FGameplayTag::RequestGameplayTag(FName("Ability.Slow"))))
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
	if (GetCurrentActorInfo()->IsNetAuthority())
	{
		if (AbilityActorClass)
		{
			AbilityActor = AAbilityActorBase::SpawnAbilityActor(GetWorld(), AbilityActorClass, GetAbilityActorSpawnLocation(), GetAbilityActorSpawnRotation(), Cast<APawn>(GetAvatarActorFromActorInfo()), Range);
		}
		if (AbilityActor)
		{
			AbilityActor->AddDamageContext(GetAvatarActorFromActorInfo(), AbilityActor, FireDamage, FrostDamage, LightningDamage, PhysicalDamage, PoisonDamage, DarkDamage);
		}
	}
}


FVector UGameplayAbilityBase::GetAbilityActorSpawnLocation()
{
	if (SpawnLocation != FVector(0.f, 0.f, 0.f))
	{
		return SpawnLocation;
	}
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

bool UGameplayAbilityBase::isFloor(FVector Normal)
{
	return (Normal.Z > abs(Normal.X) && Normal.Z > 0.f && Normal.Z > abs(Normal.Y));
}

bool UGameplayAbilityBase::isLOS(FVector Location)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetAvatarActorFromActorInfo());

	FVector StartPoint = Player->GetCameraComponent()->GetComponentLocation();
	FVector EndPoint = (Location - StartPoint) * 1.05f + StartPoint;

	FCollisionQueryParams LineTraceParams;
	LineTraceParams.bTraceComplex = false;
	LineTraceParams.bReturnPhysicalMaterial = false;
	LineTraceParams.bTraceAsyncScene = true;

	FHitResult LOSHit (ForceInit);

	if (GetWorld()->LineTraceSingleByChannel(LOSHit, StartPoint, EndPoint, ECollisionChannel::ECC_Visibility, LineTraceParams))
	{
		if (LOSHit.Location.Equals(Location, 1.f))
		{
			return true;
		}
	}
	return false;
}

FVector UGameplayAbilityBase::TraceTargetLocation()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetAvatarActorFromActorInfo());

	FVector CameraLocation = Player->GetCameraComponent()->GetComponentLocation();
	FVector StartPoint = CameraLocation;
	FVector CameraForward = Player->GetCameraComponent()->GetForwardVector();
	FVector EndPoint = CameraForward * Range + StartPoint;

	FCollisionQueryParams LineTraceParams;
	LineTraceParams.bTraceComplex = false;
	LineTraceParams.bReturnPhysicalMaterial = false;
	LineTraceParams.bTraceAsyncScene = true;

	FHitResult TraceHit(ForceInit);

	float NewRange;

	if (GetWorld()->LineTraceSingleByChannel(TraceHit, StartPoint, EndPoint, ECollisionChannel::ECC_Visibility, LineTraceParams))
	{
		if (isFloor(TraceHit.ImpactNormal))
		{
			return TraceHit.Location;
		}
		else
		{
			NewRange = TraceHit.Distance - 5.f;
		}
	}
	else
	{
		NewRange = Range;
	}
	
	while (NewRange > 0)
	{
		StartPoint = CameraForward * NewRange + CameraLocation;
		EndPoint = StartPoint - 2.f * FVector(0.f, 0.f, 1.f) * Range;

		if (GetWorld()->LineTraceSingleByChannel(TraceHit, StartPoint, EndPoint, ECollisionChannel::ECC_Visibility, LineTraceParams))
		{
			if (isLOS(TraceHit.Location) && isFloor(TraceHit.ImpactNormal))
			{
				return TraceHit.Location;
			}
		}

		NewRange -= 5.f;
	}
	
	return GetAvatarActorFromActorInfo()->GetActorLocation();
}

bool UGameplayAbilityBase::DoesAbilityTagsContain(FGameplayTag Tag) const
{
	return AbilityTags.HasTag(Tag);
}

bool UGameplayAbilityBase::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayTagContainer * SourceTags, const FGameplayTagContainer * TargetTags, OUT FGameplayTagContainer * OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	if (Cast<APlayerCharacter>(GetOwningActorFromActorInfo())->GetCharacterMovement()->IsFalling())
	{
		return false;
	}

	return true;
}
