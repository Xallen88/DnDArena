// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "SlateBrush.h"
#include "PlayerCharacter.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
class UPlayerAttributeSet;
class USpringArmComponent;
class UCameraComponent;

UENUM(BlueprintType) 
enum class AbilityInput : uint8
{
	WeaponAbility,
	WeaponAbility2,
	AreaAbility,
	AreaAbility2,
	SpecialAbility,
	SpecialAbility2,
	MeleeAbility,
	MeleeAbility2,
	DodgeLeft,
	DodgeRight,
	DodgeForward,
	DodgeBackward
};


UCLASS()
class DNDARENA_API APlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Extended PossessedBy to include GameplayAbility setttings
	void PossessedBy(AController* NewController) override;

	
private:
	// Components
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraArm;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCamera;

	// Ability system
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> WeaponAbility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> WeaponAbility2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> AreaAbility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> AreaAbility2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> SpecialAbility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> SpecialAbility2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> MeleeAbility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> MeleeAbility2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> DodgeLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> DodgeRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> DodgeForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> DodgeBackward;

	UPlayerAttributeSet* PlayerAttributeSet;

	bool bRedTeam;

public:
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UCameraComponent* GetCameraComponent() const;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void UpdateMovement();

	// UI Elements
	UFUNCTION(BlueprintCallable)
	float GetRemainingCooldownPercent(AbilityInput InputID);

	UFUNCTION(BlueprintCallable)
	FSlateBrush GetAbilityIcon(AbilityInput InputID);

	UFUNCTION()
	void OnEffectApplied (UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle);

	UFUNCTION(BlueprintNativeEvent)
	void AddBuffWidget(FActiveGameplayEffectHandle EffectHandle, FSlateBrush Icon, bool bDebuff);

	UFUNCTION(Client, Reliable)
	void AddBuffWidget_Client(FActiveGameplayEffectHandle EffectHandle, FSlateBrush Icon, bool bDebuff);
};
