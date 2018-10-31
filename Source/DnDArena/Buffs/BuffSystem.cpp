// Fill out your copyright notice in the Description page of Project Settings.

#include "BuffSystem.h"
#include "TimerManager.h"
#include "./Player/ControllerBase.h"
#include "./Player/PlayerHUD.h"
//#include "./Player/PlayerCharacter.h"
#include "Engine/Classes/GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
UBuffSystem::UBuffSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBuffSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBuffSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UBuffSystem::isStunned()
{
	return (StunStacks > 0);
}

bool UBuffSystem::isSilenced()
{
	return (SilenceStacks > 0);
}

bool UBuffSystem::isDisarmed()
{
	return (DisarmStacks > 0);
}

bool UBuffSystem::isInvulnerable()
{
	return (InvulnerableStacks > 0);
}

void UBuffSystem::ServerAttachBuff_Implementation(FName BuffName)
{
	if (BuffName == NAME_None) 
	{
		return;
	}
	if (IsImmune(BuffName))
	{
		return;
	}

	if (Buffs.Contains(BuffName)) 
	{
		ExtendBuff(BuffName);
	}
	else
	{
		AddBuff(BuffName);		
	}
}
bool UBuffSystem::ServerAttachBuff_Validate(FName BuffName)
{
	return true;
}

void UBuffSystem::ClientAttachBuffWidget_Implementation(FName BuffName, float EndTime)
{
	UPlayerHUD* PlayerHUD = Cast<AControllerBase>(Cast<APawn>(GetOwner())->GetController())->GetPlayerHUD();
	if (PlayerHUD)
	{
		PlayerHUD->AddBuffWidget(BuffName, EndTime);
	}
}

void UBuffSystem::ClientUpdateBuffWidget_Implementation(FName BuffName, float EndTime)
{
	UPlayerHUD* PlayerHUD = Cast<AControllerBase>(Cast<APawn>(GetOwner())->GetController())->GetPlayerHUD();
	if (PlayerHUD)
	{
		PlayerHUD->UpdateBuffWidget(BuffName, EndTime);
	}
}

void UBuffSystem::ClientRemoveBuffWidget_Implementation(FName BuffName)
{
	UPlayerHUD* PlayerHUD = Cast<AControllerBase>(Cast<APawn>(GetOwner())->GetController())->GetPlayerHUD();
	if (PlayerHUD)
	{
		PlayerHUD->RemoveBuffWidget(BuffName);
	}
}

void UBuffSystem::DeleteBuff(FName BuffName)
{
	ClientRemoveBuffWidget(BuffName);
	UndoBuff(BuffName);	
	Buffs.Remove(BuffName);
}

void UBuffSystem::AddBuff(FName BuffName)
{
	FBuff* Buff = BuffData->FindRow<FBuff>(BuffName, FString(""));
	if (!Buff)
	{
		return;
	}
	Buffs.Add(BuffName, *Buff);

	ClientAttachBuffWidget(BuffName, Buff->Duration + GetWorld()->GetTimeSeconds());

	ApplyBuff(BuffName);

	AddBuffTimer(BuffName);
}

void UBuffSystem::ExtendBuff(FName BuffName)
{
	FBuff* Buff = Buffs.Find(BuffName);
	if (!Buff)
	{
		return;
	}

	ClientUpdateBuffWidget(BuffName, Buff->Duration + GetWorld()->GetTimeSeconds());

	GetWorld()->GetTimerManager().ClearTimer(Buff->Timer);	

	AddBuffTimer(BuffName);
}

bool UBuffSystem::IsImmune(FName BuffName)
{
	return false;
}

void UBuffSystem::AddBuffTimer(FName BuffName)
{
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	FBuff* Buff = Buffs.Find(BuffName);
	if (!Buff)
	{
		return;
	}
	float Duration = Buff->Duration;
	
	TimerDelegate = FTimerDelegate::CreateUObject(this, &UBuffSystem::DeleteBuff, BuffName);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, Duration, false);

	Buff->Timer = TimerHandle;
}

void UBuffSystem::ApplyBuff(FName BuffName)
{
	BuffEffectSwitch(BuffName, true);
}

void UBuffSystem::UndoBuff(FName BuffName)
{
	BuffEffectSwitch(BuffName, false);
}

void UBuffSystem::BuffEffectSwitch(FName BuffName, bool bApply)
{
	FBuff* Buff = Buffs.Find(BuffName);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner());

	if (!Buff || !PlayerCharacter)
	{
		return;
	}

	switch (Buff->Type)
	{
	case EBuffType::Invulnerability:
		InvulnerabilityEffect(bApply);
		break;
	case EBuffType::MovementSpeedMulti:
		MovementEffect(PlayerCharacter, Buff->Multiplier, bApply);
		break;
	case EBuffType::Snare: 
		SnareEffect(PlayerCharacter, bApply);
		break;
	}
}

void UBuffSystem::MovementEffect(APlayerCharacter * PlayerCharacter, float Multiplier, bool bApply)
{
	UCharacterMovementComponent* Movement = PlayerCharacter->GetCharacterMovement();
	if (bApply)
	{
		Movement->MaxWalkSpeed *= Multiplier;
	}
	else
	{
		Movement->MaxWalkSpeed /= Multiplier;
	}
}

void UBuffSystem::SnareEffect(APlayerCharacter * PlayerCharacter, bool bApply)
{
	UCharacterMovementComponent* Movement = PlayerCharacter->GetCharacterMovement();
	if (bApply)
	{
		Movement->StopMovementImmediately();
		Movement->DisableMovement();
	}
	else
	{
		Movement->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

void UBuffSystem::InvulnerabilityEffect(bool bApply)
{
	bApply ? ++InvulnerableStacks : --InvulnerableStacks;
}
