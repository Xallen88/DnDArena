// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayAbilityBase.h"
#include "AbilityActorBase.h"
#include "AbilityTask_SpawnActor.h"

void UGameplayAbilityBase::ExecutionLogic()
{		
	if (DoesAbilityTagsContain(FGameplayTag::RequestGameplayTag(FName("Ability.Projectile"))))
	{ 		
		ProjectileExecution();
	}
}

void UGameplayAbilityBase::ProjectileExecution()
{
	/*FGameplayAbilityTargetData_LocationInfo SpawnActorTargetData;
	FGameplayAbilityTargetingLocationInfo SpawnActorLocation;
	SpawnActorLocation.LiteralTransform = GetAvatarActorFromActorInfo()->GetActorTransform();
	SpawnActorTargetData.TargetLocation = SpawnActorLocation;
	FGameplayAbilityTargetDataHandle SpawnActorTargetDataHandle = FGameplayAbilityTargetDataHandle(&SpawnActorTargetData);*/

	UClass* SpawnClass = AbilityActor->GeneratedClass;
	//TSubclassOf<AActor> SpawnSubclass = SpawnClass;

	if (SpawnClass->IsChildOf(AAbilityActorBase::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("IS CHILD OF"));
	}

	//UAbilityTask_SpawnActor* SpawnActorTask = UAbilityTask_SpawnActor::SpawnActor(this, SpawnActorTargetDataHandle,SpawnSubclass);

	//TScriptDelegate<FWeakObjectPtr> SpawnActorScriptDelegate;
	//SpawnActorScriptDelegate.BindUFunction(this, FName("AbilityActorSetup"));
	//FSpawnActorDelegate SpawnActorDelegate;
	//SpawnActorDelegate.Add(SpawnActorScriptDelegate);
	//SpawnActorTask->Success = SpawnActorDelegate;

	/*AActor* SpawnedActor;
	SpawnActorTask->BeginSpawningActor(this, SpawnActorTargetDataHandle,SpawnSubclass, SpawnedActor);
	UE_LOG(LogTemp, Warning, TEXT("BEGIN SPAWN"));
	SpawnActorTask->FinishSpawningActor(this, SpawnActorTargetDataHandle, SpawnedActor);
	UE_LOG(LogTemp, Warning, TEXT("FINISH SPAWN"));*/
	
	
	/*const FGameplayAbilityActivationInfo* ActivationInfo = &CurrentActivationInfo;
	if (HasAuthority(ActivationInfo))
	{
		UClass* ClassName = AbilityActor->GeneratedClass;
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = Cast<APawn>(GetAvatarActorFromActorInfo());
		GetWorld()->SpawnActor<AAbilityActorBase>(ClassName, GetAbilityActorSpawnLocation(), GetAbilityActorSpawnRotation(), SpawnParams);
	}*/
}

void UGameplayAbilityBase::AbilityActorSetup(AActor * ActorToSetup)
{
	ActorToSetup->SetActorLocation(GetAbilityActorSpawnLocation());
	ActorToSetup->SetActorRotation(GetAbilityActorSpawnRotation());
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
