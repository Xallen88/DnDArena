// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Buff.h"
#include "BuffWidget.h"
#include "BuffSystem.generated.h"

class APlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType)
class DNDARENA_API UBuffSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuffSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:	
	UPROPERTY(EditAnywhere, Category = "Buff Data")
		UDataTable* BuffData;

	int32 StunStacks;
	int32 SilenceStacks;
	int32 DisarmStacks;
	int32 InvulnerableStacks;
	
	TMap<FName, FBuff> Buffs;

	UFUNCTION()
	void DeleteBuff(FName BuffName);

	void AddBuff(FName BuffName);

	void ExtendBuff(FName BuffName);
	
	UFUNCTION(BlueprintCallable, Category = "Buff", Client, Reliable)
		void ClientAttachBuffWidget(FName BuffName, float EndTime);

	UFUNCTION(BlueprintCallable, Category = "Buff", Client, Reliable)
		void ClientUpdateBuffWidget(FName BuffName, float EndTime);

	UFUNCTION(BlueprintCallable, Category = "Buff", Client, Reliable)
		void ClientRemoveBuffWidget(FName BuffName);

	bool IsImmune(FName BuffName);

	void AddBuffTimer(FName BuffName);

	void ApplyBuff(FName BuffName);

	void UndoBuff(FName BuffName);

	void BuffEffectSwitch(FName BuffName, bool bApply);

	void MovementEffect(APlayerCharacter* PlayerCharacter, float Multiplier, bool bApply);

	void SnareEffect(APlayerCharacter* PlayerCharacter, bool bApply);

	void InvulnerabilityEffect(bool bApply);


public:
	// Called when buff is being created/refreshed
	UFUNCTION(BlueprintCallable, Category = "Buff", Server, Reliable, WithValidation)
		void ServerAttachBuff(FName BuffName);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool isStunned();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool isSilenced();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool isDisarmed();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool isInvulnerable();
};
