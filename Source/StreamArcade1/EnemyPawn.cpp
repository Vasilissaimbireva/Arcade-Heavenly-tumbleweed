// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Components/StaticMeshComponent.h"
#include "StremArcade1GameModeBase.h"
#include "Sound/SoundBase.h"
#include "Engine/World.h"


AEnemyPawn::AEnemyPawn()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	RootComponent = PawnCollision;
	
	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(PawnCollision, NAME_None);
	
	ShootComponent = CreateDefaultSubobject<UShootComponent1>(TEXT("ShootComponent"));
	HealthComponent= CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnHealthEnded.AddDynamic(this, &AEnemyPawn::KillPawn);

	OnActorBeginOverlap.AddDynamic(this, &AEnemyPawn::OnEnemyOverlap);

}

void AEnemyPawn::KillPawn()
{
	AStremArcade1GameModeBase* GameMode = Cast<AStremArcade1GameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode) GameMode->AddPoints(DestroyPoints);

	SpawnBonuses();
	DestroyPawn();
}

void AEnemyPawn::DestroyPawn()
{
	if (DestroyParticle)
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);

	if (CollectSound)
	UGameplayStatics::SpawnSound2D(GetWorld(), CollectSound, 3.0f, 1.0f, 0.0f, (USoundConcurrency*) nullptr, true);

	Destroy();
}

void AEnemyPawn::OnEnemyOverlap(AActor* OverlapedActor, AActor* OtherActor)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(this, 0)) return;
	float AppliedDamage = UGameplayStatics::ApplyDamage(OtherActor, 100.f, GetController(), this, UDamageType::StaticClass());
	if (AppliedDamage >0.f) DestroyPawn();
}

void AEnemyPawn::SpawnBonuses()
{
	FRandomStream Random;
	Random.GenerateNewSeed();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	
	for (FBonusChance Bonus : PossibleBonuses) 
	{	
		float RandChance = Random.RandRange(0.f, 100.f);
		if (RandChance < Bonus.Chance)
		{
			GetWorld()->SpawnActor<ABonus>(Bonus.BonusClass, GetActorLocation(), FRotator(0.f), SpawnParameters);
		}
		
	}

}


void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	float WorldMoveOffset = -100.f * DeltaTime;
	AddActorWorldOffset(FVector(WorldMoveOffset, 0.f, 0.f));

}

