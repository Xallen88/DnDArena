// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Buff.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EBuffType {
	DamageOverTime,
	Stun,
	Silence, 
	Disarm,
	Snare,
	MovementSpeedMulti,
	DamageTakenMulti,
	ResistanceMulti,
	DamageMulti,
	CastTimeMulti,
	AttackSpeedMulti,
	Invulnerability
};

USTRUCT(BlueprintType)
struct FBuff : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
		FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FSlateBrush Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EBuffType> Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTimerHandle Timer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Multiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bDebuff;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCC;
	
};
