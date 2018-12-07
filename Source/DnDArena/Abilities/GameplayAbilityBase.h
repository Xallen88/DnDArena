// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilityBase.generated.h"

class AAbilityActorBase;

/**
 * 
 */
UCLASS()
class DNDARENA_API UGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

private:
	bool SpawnAbilityActor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation, meta = (AllowPrivateAccess = "true"))
		UAnimMontage* AbilityAnimation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Execution, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AAbilityActorBase> AbilityActorClass;

	UPROPERTY()
		AAbilityActorBase* AbilityActor;

	UFUNCTION(BlueprintCallable, Category = Ability)
		virtual void ExecutionLogic();

	UFUNCTION()
		virtual void ProjectileExecution();
	
	UFUNCTION()
		FVector GetAbilityActorSpawnLocation();

	UFUNCTION()
		FRotator GetAbilityActorSpawnRotation();
	
public:
	virtual uint8 GetGameplayTaskDefaultPriority() const override { return FGameplayTasks::DefaultPriority; }
	
	UFUNCTION(BlueprintCallable, Category = Ability)
		bool DoesAbilityTagsContain(FGameplayTag Tag) const;

	
};
