// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Effects/DamageContext.h"
#include "SlateBrush.h"
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
	void ApplyMovementEffect();

	void RemoveMovementEffect();

protected:
	// Blueprint variables - These variables require a default value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Execution, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AAbilityActorBase> AbilityActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AbilitySpecs, meta = (AllowPrivateAccess = "true"))
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySpecs|Damage", meta = (AllowPrivateAccess = "true"))
	float FireDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySpecs|Damage", meta = (AllowPrivateAccess = "true"))
	float FrostDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySpecs|Damage", meta = (AllowPrivateAccess = "true"))
	float LightningDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySpecs|Damage", meta = (AllowPrivateAccess = "true"))
	float PhysicalDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySpecs|Damage", meta = (AllowPrivateAccess = "true"))
	float PoisonDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySpecs|Damage", meta = (AllowPrivateAccess = "true"))
	float DarkDamage;

	// Variables
	UPROPERTY()
	AAbilityActorBase* AbilityActor;

	FVector SpawnLocation;

	// Functions
	UFUNCTION(BlueprintCallable, Category = Ability)
	virtual void ExecutionLogic();
		
	UFUNCTION()
	FVector GetAbilityActorSpawnLocation();

	UFUNCTION()
	FRotator GetAbilityActorSpawnRotation();

	bool isFloor(FVector Normal);

	bool isLOS(FVector Location);
	
	
public:
	virtual uint8 GetGameplayTaskDefaultPriority() const override { return FGameplayTasks::DefaultPriority; } // Couldn't compile without this
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Display, meta = (AllowPrivateAccess = "true"))
	FSlateBrush AbilityIcon;
	
	UFUNCTION(BlueprintCallable, Category = Ability)
	bool DoesAbilityTagsContain(FGameplayTag Tag) const;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	FVector TraceTargetLocation();
};
