// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "DamageCalculation.h"
#include "DamageContext.h"

void UDamageCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters & ExecutionParams, OUT FGameplayEffectCustomExecutionOutput & OutExecutionOutput) const
{
	FDamageContext* DamageContext = (FDamageContext*)(ExecutionParams.GetOwningSpec().GetContext().Get());
	TMap<FString, float> DamageMatrix = DamageContext->GetDamageMatrix();
	float PhysD = *DamageMatrix.Find(FString("Physical"));
	
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::SanitizeFloat(*DamageMatrix.Find(FString("Physical"))));
}
