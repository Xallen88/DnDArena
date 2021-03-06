// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "./Buffs/BuffSystem.h"
#include "./Abilities/PlayerAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "UnrealNetwork.h"
#include "Abilities/AbilityActorBase.h"
#include "GameplayEffect.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Abilities/GameplayAbilityBase.h"
#include "Effects/GameplayEffectUIDataBasic.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->RelativeRotation = FRotator(0.f, 0.f, 0.f);	
	CameraArm->TargetArmLength = 300.f;
	CameraArm->bEnableCameraLag = true;
	CameraArm->CameraLagSpeed = 12.0f;
	CameraArm->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	PlayerCamera->RelativeLocation = FVector(-200.f, 0.f, 100.f);

	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));	

	PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("AttributeSet"));

	if (PlayerAttributeSet)
	{
		PlayerAttributeSet->SetInitValue(PlayerAttributeSet->MaxHealth, 1000.f);
		PlayerAttributeSet->SetInitValue(PlayerAttributeSet->Health, 600.f);
		PlayerAttributeSet->SetInitValue(PlayerAttributeSet->FireResistance, 10.f);
		PlayerAttributeSet->SetInitValue(PlayerAttributeSet->FrostResistance, 10.f);
		PlayerAttributeSet->SetInitValue(PlayerAttributeSet->LightningResistance, 10.f);
		PlayerAttributeSet->SetInitValue(PlayerAttributeSet->PhysicalResistance, 10.f);
		PlayerAttributeSet->SetInitValue(PlayerAttributeSet->PoisonResistance, 10.f);
		PlayerAttributeSet->SetInitValue(PlayerAttributeSet->DarkResistance, 10.f);

		PlayerAttributeSet->SetInitValue(PlayerAttributeSet->MaxResource, 1000.f);
		PlayerAttributeSet->SetInitValue(PlayerAttributeSet->Resource, 800.f);
		PlayerAttributeSet->SetInitValue(PlayerAttributeSet->AttackSpeed, 1.f);
		PlayerAttributeSet->SetInitValue(PlayerAttributeSet->CastSpeed, 1.f);

		PlayerAttributeSet->SetInitValue(PlayerAttributeSet->MovementSpeed, 600.f);
		PlayerAttributeSet->SetInitValue(PlayerAttributeSet->DodgeCharges, 2.f);
	}
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Setup AbilitySystemComponent and ability inputs
	if (AbilitySystem)
	{		
		if (HasAuthority())
		{
			if(WeaponAbility)			
			{
				AbilitySystem->GiveAbility(FGameplayAbilitySpec(WeaponAbility.GetDefaultObject(), 1, static_cast<int>(AbilityInput::WeaponAbility)));
			}
			if (WeaponAbility2)
			{
				AbilitySystem->GiveAbility(FGameplayAbilitySpec(WeaponAbility2.GetDefaultObject(), 1, static_cast<int>(AbilityInput::WeaponAbility2)));
			}
			if (AreaAbility)
			{
				AbilitySystem->GiveAbility(FGameplayAbilitySpec(AreaAbility.GetDefaultObject(), 1, static_cast<int>(AbilityInput::AreaAbility)));
			}
			if (AreaAbility2)
			{
				AbilitySystem->GiveAbility(FGameplayAbilitySpec(AreaAbility2.GetDefaultObject(), 1, static_cast<int>(AbilityInput::AreaAbility2)));
			}
			if (SpecialAbility)
			{
				AbilitySystem->GiveAbility(FGameplayAbilitySpec(SpecialAbility.GetDefaultObject(), 1, static_cast<int>(AbilityInput::SpecialAbility)));
			}
			if (SpecialAbility2)
			{
				AbilitySystem->GiveAbility(FGameplayAbilitySpec(SpecialAbility2.GetDefaultObject(), 1, static_cast<int>(AbilityInput::SpecialAbility2)));
			}
			if (MeleeAbility)
			{
				AbilitySystem->GiveAbility(FGameplayAbilitySpec(MeleeAbility.GetDefaultObject(), 1, static_cast<int>(AbilityInput::MeleeAbility)));
			}
			if (MeleeAbility2)
			{
				AbilitySystem->GiveAbility(FGameplayAbilitySpec(MeleeAbility2.GetDefaultObject(), 1, static_cast<int>(AbilityInput::MeleeAbility2)));
			}
			if (DodgeLeft)
			{
				AbilitySystem->GiveAbility(FGameplayAbilitySpec(DodgeLeft.GetDefaultObject(), 1, static_cast<int>(AbilityInput::DodgeLeft)));
			}
			if (DodgeRight)
			{
				AbilitySystem->GiveAbility(FGameplayAbilitySpec(DodgeRight.GetDefaultObject(), 1, static_cast<int>(AbilityInput::DodgeRight)));
			}
			if (DodgeForward)
			{
				AbilitySystem->GiveAbility(FGameplayAbilitySpec(DodgeLeft.GetDefaultObject(), 1, static_cast<int>(AbilityInput::DodgeForward)));
			}
			if (DodgeBackward)
			{
				AbilitySystem->GiveAbility(FGameplayAbilitySpec(DodgeLeft.GetDefaultObject(), 1, static_cast<int>(AbilityInput::DodgeBackward)));
			}
		}

		AbilitySystem->InitAbilityActorInfo(this, this);

		AbilitySystem->OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &APlayerCharacter::OnEffectApplied);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	AbilitySystem->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbilityInputBinds("ConfirmInput", "CancelInput", "AbilityInput"));
	
}

void APlayerCharacter::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);
	
	AbilitySystem->RefreshAbilityActorInfo();
}

UAbilitySystemComponent * APlayerCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

UCameraComponent * APlayerCharacter::GetCameraComponent() const
{
	return PlayerCamera;
}

float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (!DamageCauser->IsA<AAbilityActorBase>())
	{
		return 0.f;
	}

	AAbilityActorBase* DamagingAbilityActor = Cast<AAbilityActorBase>(DamageCauser);
	TArray<TSubclassOf<UGameplayEffect>> EffectArray = DamagingAbilityActor->GetEffects();	

	for (int32 i = 0; i < EffectArray.Num(); ++i)
	{
		UGameplayEffect* GameplayEffect = EffectArray[i].GetDefaultObject();
		AbilitySystem->ApplyGameplayEffectToSelf(GameplayEffect, 1, DamagingAbilityActor->GetDamageContextHandle());
	}

	return 0.f;
}

void APlayerCharacter::UpdateMovement()
{
	UCharacterMovementComponent* CharacterMovement = GetCharacterMovement();
	if (PlayerAttributeSet->MovementSpeed.GetCurrentValue() == 0)
	{
		CharacterMovement->StopMovementImmediately();
		CharacterMovement->DisableMovement();
	}
	else
	{
		CharacterMovement->MaxWalkSpeed = PlayerAttributeSet->MovementSpeed.GetCurrentValue();
		if (CharacterMovement->MovementMode == EMovementMode::MOVE_None)
		{
			CharacterMovement->SetMovementMode(EMovementMode::MOVE_Walking);
		}
	}	
}

float APlayerCharacter::GetRemainingCooldownPercent(AbilityInput InputID)
{
	FGameplayAbilitySpec* AbilitySpec = AbilitySystem->FindAbilitySpecFromInputID(static_cast<int>(InputID));
	if (AbilitySpec)
	{
		float CooldownDuration;
		float CooldownRemaining;
		AbilitySpec->Ability->GetCooldownTimeRemainingAndDuration(AbilitySpec->Handle, AbilitySystem->AbilityActorInfo.Get(), CooldownRemaining, CooldownDuration);
		if (CooldownDuration > 0) 
		{
			return CooldownRemaining/CooldownDuration;
		}
	}
	return 0.0f;
}

FSlateBrush APlayerCharacter::GetAbilityIcon(AbilityInput InputID)
{
	FGameplayAbilitySpec* AbilitySpec = AbilitySystem->FindAbilitySpecFromInputID(static_cast<int>(InputID));
	if (AbilitySpec)
	{
		return Cast<UGameplayAbilityBase>(AbilitySpec->Ability)->AbilityIcon;
	}
	return FSlateBrush();
}

void APlayerCharacter::OnEffectApplied(UAbilitySystemComponent * ASC, const FGameplayEffectSpec & EffectSpec, FActiveGameplayEffectHandle EffectHandle)
{
	if (HasAuthority())
	{
		FGameplayTagContainer EffectTags;
		EffectSpec.GetAllAssetTags(EffectTags);
		if (EffectTags.HasTag(FGameplayTag::RequestGameplayTag(FName("Effect.Debuff"))))
		{
			FSlateBrush Icon = Cast<UGameplayEffectUIDataBasic>(EffectSpec.Def->UIData)->EffectIcon;
			AddBuffWidget_Client(EffectHandle, Icon, true);
		}
		if (EffectTags.HasTag(FGameplayTag::RequestGameplayTag(FName("Effect.Buff"))))
		{
			FSlateBrush Icon = Cast<UGameplayEffectUIDataBasic>(EffectSpec.Def->UIData)->EffectIcon;
			AddBuffWidget_Client(EffectHandle, Icon, false);
		}
	}
}

void APlayerCharacter::AddBuffWidget_Client_Implementation(FActiveGameplayEffectHandle EffectHandle, FSlateBrush Icon, bool bDebuff)
{
	AddBuffWidget(EffectHandle, Icon, bDebuff);
}

void APlayerCharacter::AddBuffWidget_Implementation(FActiveGameplayEffectHandle EffectHandle, FSlateBrush Icon, bool bDebuff)
{
}

