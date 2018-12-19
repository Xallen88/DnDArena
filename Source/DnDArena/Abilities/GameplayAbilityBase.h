// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Effects/DamageContext.h"
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

	void ApplyMovementEffect();

	void RemoveMovementEffect();

protected:
	// Blueprint variables - These variables require a default value	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Execution, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AAbilityActorBase> AbilityActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage, meta = (AllowPrivateAccess = "true"))
		float FireDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage, meta = (AllowPrivateAccess = "true"))
		float FrostDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage, meta = (AllowPrivateAccess = "true"))
		float LightningDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage, meta = (AllowPrivateAccess = "true"))
		float PhysicalDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage, meta = (AllowPrivateAccess = "true"))
		float PoisonDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage, meta = (AllowPrivateAccess = "true"))
		float DarkDamage;

	// Variables
	UPROPERTY()
		AAbilityActorBase* AbilityActor;

	// Functions
	UFUNCTION(BlueprintCallable, Category = Ability)
		virtual void ExecutionLogic();

	UFUNCTION()
		virtual void ProjectileExecution();
	
	UFUNCTION()
		FVector GetAbilityActorSpawnLocation();

	UFUNCTION()
		FRotator GetAbilityActorSpawnRotation();
	
public:
	virtual uint8 GetGameplayTaskDefaultPriority() const override { return FGameplayTasks::DefaultPriority; } // Couldn't compile without this
	
	UFUNCTION(BlueprintCallable, Category = Ability)
		bool DoesAbilityTagsContain(FGameplayTag Tag) const;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	
};
