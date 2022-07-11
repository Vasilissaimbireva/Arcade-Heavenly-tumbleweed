// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "GameFramework/DamageType.h"
#include "Components/StaticMeshComponent.h"


AShootProjectile::AShootProjectile()
	:
	ProjectileSpeed(500.f)
{
 	
	PrimaryActorTick.bCanEverTick = true;


	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	RootComponent = Collision;
	

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision, NAME_None);

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->SetupAttachment(Collision);

}


void AShootProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner())
	{
		Collision->IgnoreActorWhenMoving(GetOwner(), true);

	}

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AShootProjectile::OnProjectileOverlap);
	
}

void AShootProjectile::OnProjectileOverlap(UPrimitiveComponent* OpelappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodeIndex, bool Sweep, const FHitResult& Hit)
{
	if (!OtherActor || !Cast<APawn>(OtherActor)) return; 

	if (!GetOwner()) return;
	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if (!PawnOwner) return;

	AController* execOnRep_Instigator = PawnOwner->GetController();
	
	UGameplayStatics::ApplyDamage(OtherActor, Damage, execOnRep_Instigator, this, UDamageType::StaticClass());

	Destroy();
}

void AShootProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalOffset(FVector(ProjectileSpeed * DeltaTime, 0.f, 0.f));
}

