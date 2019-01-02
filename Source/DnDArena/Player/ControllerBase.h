// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerHUD.h"
#include "GameplayEffectTypes.h"
#include "ControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class DNDARENA_API AControllerBase : public APlayerController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	/*virtual void BeginPlay () override;*/

public:
	UFUNCTION(BlueprintGetter)
	UPlayerHUD* GetPlayerHUD();

	UFUNCTION(BlueprintSetter)
	void SetPlayerHUD(UPlayerHUD* PHUD);

private:
	UPROPERTY(BlueprintSetter=SetPlayerHUD)
	UPlayerHUD* PlayerHUD;

	
	
};
