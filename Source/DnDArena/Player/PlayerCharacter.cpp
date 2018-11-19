// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "./Buffs/BuffSystem.h"
#include "./Abilities/PlayerAttributeSet.h"
#include "AbilitySystemComponent.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	}
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystem)
	{	
		if (HasAuthority() && Ability)
		{
			AbilitySystem->GiveAbility(FGameplayAbilitySpec(Ability.GetDefaultObject(), 1, static_cast<int>(AbilityInput::WeaponAttack2)));
		}
		AbilitySystem->InitAbilityActorInfo(this, this);
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

