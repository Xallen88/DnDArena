// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "./Buffs/BuffWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class DNDARENA_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent)
		bool AddBuffWidget(FName BuffName, float EndTime);

	UFUNCTION(BlueprintNativeEvent)
		bool UpdateBuffWidget(FName BuffName, float EndTime);

	UFUNCTION(BlueprintNativeEvent)
		bool RemoveBuffWidget(FName BuffName);


private:	
	
};
