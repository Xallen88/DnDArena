// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "PlayerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class DNDARENA_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	// Defences
	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	UFUNCTION()
	void OnRep_Health();

	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	UFUNCTION()
	void OnRep_MaxHealth();

	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData FireResistance;

	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData FrostResistance;

	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData LightningResistance;

	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData PhysicalResistance;

	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData PoisonResistance;

	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData DarkResistance;

	// Ability Related
	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Resource)
	FGameplayAttributeData Resource;
	UFUNCTION()
	void OnRep_Resource();

	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxResource)
	FGameplayAttributeData MaxResource;
	UFUNCTION()
	void OnRep_MaxResource();

	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_AttackSpeed)
	FGameplayAttributeData AttackSpeed;
	UFUNCTION()
	void OnRep_AttackSpeed();

	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_CastSpeed)
	FGameplayAttributeData CastSpeed;
	UFUNCTION()
	void OnRep_CastSpeed();

	// Movement
	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MovementSpeed)
	FGameplayAttributeData MovementSpeed;
	UFUNCTION()
	void OnRep_MovementSpeed();

	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_DodgeCharges)
	FGameplayAttributeData DodgeCharges;
	UFUNCTION()
	void OnRep_DodgeCharges();

public:
	void SetInitValue(FGameplayAttributeData& AttributeData, float InitValue);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
};
