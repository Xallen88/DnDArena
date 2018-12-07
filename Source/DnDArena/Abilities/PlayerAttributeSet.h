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
	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
		FGameplayAttributeData Health;

	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
		FGameplayAttributeData MaxHealth;

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

	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
		FGameplayAttributeData MaxResource;

	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
		FGameplayAttributeData AttackSpeed;

	UPROPERTY(Category = "Attributes", EditAnywhere, BlueprintReadWrite)
		FGameplayAttributeData CastSpeed;

public:
	void SetInitValue(FGameplayAttributeData& AttributeData, float InitValue);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
};
