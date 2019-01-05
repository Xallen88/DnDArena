// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Effects/DamageContext.h"
#include "GameplayEffect.h"
#include "Components/SceneComponent.h"
#include "AbilityActorBase.generated.h"

UCLASS()
class DNDARENA_API AAbilityActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbilityActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilityActor, meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultScene;

protected:
	FGameplayEffectContextHandle DamageContextHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayEffect>> Effects;

	TArray<class APlayerCharacter*> ExcludedPlayers;

	void BuildExclusionList ();


public:
	virtual void AddDamageContext(AActor* Instigator, AActor* DamageCauser, float FireDamage, float FrostDamage, float LightningDamage, float PhysicalDamage, float PoisonDamage, float DarkDamage);

	FGameplayEffectContextHandle GetDamageContextHandle();

	TArray<TSubclassOf<UGameplayEffect>> GetEffects();

	virtual void Activate ();
};
