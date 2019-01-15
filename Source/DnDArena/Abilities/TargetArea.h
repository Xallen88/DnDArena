// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayAbilityBase.h"
#include "Components/SceneComponent.h"
#include "Components/DecalComponent.h"
#include "TargetArea.generated.h"

UCLASS()
class DNDARENA_API ATargetArea : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetArea();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilityActor, meta = (AllowPrivateAccess = "true"))
	UDecalComponent* Decal;

	UFUNCTION(BlueprintCallable)
	FLinearColor ColourSwitch();

public:
	UGameplayAbilityBase* Ability;
	
};
