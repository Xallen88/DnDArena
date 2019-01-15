// Copyright 2018-2019 Xallenia Studios. All Rights Reserved.

#include "Weapon.h"
#include "Engine/World.h"
#include "Gamestates/VersusGamestate.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultScene = CreateDefaultSubobject<USceneComponent>(FName("Default Scene"));
	DefaultScene = RootComponent;

	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(FName("Collision Capsule"));
	if (CollisionCapsule)
	{
		CollisionCapsule->SetCollisionProfileName(FName("Projectile"));
		CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnOverlapBegin);
		CollisionCapsule->SetupAttachment(RootComponent);
	}
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	if (StaticMesh && CollisionCapsule)
	{
		StaticMesh->SetupAttachment(CollisionCapsule);
	}
	
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetInstigator())
	{
		ExclusionList = GetWorld()->GetGameState<AVersusGamestate>()->GetTeam(Cast<APlayerCharacter>(GetInstigator()));
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->IsA<APlayerCharacter>() && !ExclusionList.Contains(OtherActor))
	{
		UGameplayStatics::ApplyPointDamage(OtherActor, 1.f, SweepResult.ImpactNormal, SweepResult, GetInstigatorController(), this, UDamageType::StaticClass());
		ExclusionList.Add(Cast<APlayerCharacter>(OtherActor));
	}
}

