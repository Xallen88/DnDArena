// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityActorBase.h"
#include "GameplayAbilityBase.h"

void UGameplayAbilityBase::ExecutionLogic()
{		
	if (DoesAbilityTagsContain(FGameplayTag::RequestGameplayTag(FName("Ability.Projectile"))))
	{ 
		const FGameplayAbilityActivationInfo* ActivationInfo = &CurrentActivationInfo;
		if (HasAuthority(ActivationInfo))
		{
			UClass* ClassName = AbilityActor->GeneratedClass;
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParams.Instigator = Cast<APawn>(GetAvatarActorFromActorInfo());
			GetWorld()->SpawnActor<AAbilityActorBase>(ClassName, GetAbilityActorSpawnLocation(), GetAbilityActorSpawnRotation(), SpawnParams);
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetAbilityActorSpawnLocation().ToString());
		}		
	}
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
