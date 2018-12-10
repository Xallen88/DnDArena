// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "DamageCalculation.h"
#include "DamageContext.h"
#include "AbilitySystemComponent.h"
#include "Abilities/PlayerAttributeSet.h"

// Attributes used in this calculation
struct CalculationAttributes
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FrostResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PoisonResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DarkResistance);

	CalculationAttributes()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, Health, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, FireResistance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, FrostResistance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, LightningResistance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, PhysicalResistance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, PoisonResistance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, DarkResistance, Source, false);
	}
};

UDamageCalculation::UDamageCalculation(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CalculationAttributes Attributes;

	RelevantAttributesToCapture.Add(Attributes.HealthDef);
	RelevantAttributesToCapture.Add(Attributes.FireResistanceDef);
	RelevantAttributesToCapture.Add(Attributes.FrostResistanceDef);
	RelevantAttributesToCapture.Add(Attributes.LightningResistanceDef);
	RelevantAttributesToCapture.Add(Attributes.PhysicalResistanceDef);
	RelevantAttributesToCapture.Add(Attributes.PoisonResistanceDef);
	RelevantAttributesToCapture.Add(Attributes.DarkResistanceDef);
}

float DamageDone(float DamageIn, float Resistance)
{
	return (100.f - Resistance) / 100 * DamageIn;
}

void UDamageCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters & ExecutionParams, OUT FGameplayEffectCustomExecutionOutput & OutExecutionOutput) const
{
	CalculationAttributes Attributes;
	FAggregatorEvaluateParameters EvaluationParams;

	FDamageContext* DamageContext = (FDamageContext*)(ExecutionParams.GetOwningSpec().GetContext().Get());
	TMap<FString, float> DamageMatrix = DamageContext->GetDamageMatrix();
		
	float DamageValue = 0.f;
	float DamageOut = 0.f;
	float Resistance = 0.f;
	if ((DamageValue = *DamageMatrix.Find(FString("Fire"))) > 0)
	{
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Attributes.FireResistanceDef, EvaluationParams, Resistance);
		DamageOut += DamageDone(DamageValue, Resistance);
		// Relevant damage specific code
	}
	if ((DamageValue = *DamageMatrix.Find(FString("Frost"))) > 0)
	{
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Attributes.FrostResistanceDef, EvaluationParams, Resistance);
		DamageOut += DamageDone(DamageValue, Resistance);
		// Relevant damage specific code
	}
	if ((DamageValue = *DamageMatrix.Find(FString("Lightning"))) > 0)
	{
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Attributes.LightningResistanceDef, EvaluationParams, Resistance);
		DamageOut += DamageDone(DamageValue, Resistance);
		// Relevant damage specific code
	}
	if ((DamageValue = *DamageMatrix.Find(FString("Physical"))) > 0)
	{
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Attributes.PhysicalResistanceDef, EvaluationParams, Resistance);
		DamageOut += DamageDone(DamageValue, Resistance);
		// Relevant damage specific code
	}
	if ((DamageValue = *DamageMatrix.Find(FString("Poison"))) > 0)
	{
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Attributes.PoisonResistanceDef, EvaluationParams, Resistance);
		DamageOut += DamageDone(DamageValue, Resistance);
		// Relevant damage specific code
	}
	if ((DamageValue = *DamageMatrix.Find(FString("Dark"))) > 0)
	{
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Attributes.DarkResistanceDef, EvaluationParams, Resistance);
		DamageOut += DamageDone(DamageValue, Resistance);
		// Relevant damage specific code
	}
	
	float Health = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(Attributes.HealthDef, EvaluationParams, Health);

	if (DamageOut > 0.f)
	{
		if (DamageOut < Health) 
		{
			OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(Attributes.HealthProperty, EGameplayModOp::Additive, -DamageOut));
		}
		else
		{
			OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(Attributes.HealthProperty, EGameplayModOp::Additive, -Health));
			// Call death function on actor
		}
	}
}
