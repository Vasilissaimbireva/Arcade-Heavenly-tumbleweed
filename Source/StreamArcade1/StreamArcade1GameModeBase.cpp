// Copyright Epic Games, Inc. All Rights Reserved.


#include "StremArcade1GameModeBase.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "MyPawn.h"

AStremArcade1GameModeBase::AStremArcade1GameModeBase():
	PlayerRecoverTime(3),
	CurrentShootLevel(-1),
	IncreaseDifficultyPeriod(5.f)
{
	EnemySpawnController = CreateDefaultSubobject<UEnemySpawnController>(TEXT("EnemySpawnController"));
	HealthsComponent = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthsComponent"));
}

void AStremArcade1GameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HealthsComponent->HealthsEnded.AddDynamic(this, &AStremArcade1GameModeBase::EndGame);

	MyPawn = Cast<AMyPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (!MyPawn) return;

	ChangeShootLevel(true);

	MyPawn->PawnDamaged.AddDynamic(this, &AStremArcade1GameModeBase::ExplodePawn);

	GetWorld()->GetTimerManager().SetTimer(IncreaseDifficultyTimer, this, &AStremArcade1GameModeBase::IncreaseDifficulty, IncreaseDifficultyPeriod, true);
}

void AStremArcade1GameModeBase::ExplodePawn_Implementation()
{
	MyPawn->ExplodePawn();

	HealthsComponent->ChangeHealths(-1);

	ChangeShootLevel(false);

	if (!IsGameOver)
	GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &AStremArcade1GameModeBase::RecoverPawn, PlayerRecoverTime, false);

}

void AStremArcade1GameModeBase::RecoverPawn_Implementation()
{
	MyPawn->RecoverPawn();
}

void AStremArcade1GameModeBase::EndGame()
{
	IsGameOver = true;

	EnemySpawnController->SetActive(false);

	GameOver.Broadcast();

	UGameplayStatics::GetPlayerPawn(this, 0)->Destroy();
	
	
}

void AStremArcade1GameModeBase::IncreaseDifficulty()
{
	EnemySpawnController->ChangeStageTimeMultiplier = FMath::Max(EnemySpawnController->ChangeStageTimeMultiplier * 0.95, 0.4);
}

void AStremArcade1GameModeBase::AddPoints(int Points)
{
	GamePoints += Points;
}


bool AStremArcade1GameModeBase::ChangeShootLevel(bool Up)
{
	MyPawn = Cast<AMyPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (!MyPawn) return false;

	int NewLevel = FMath::Clamp(CurrentShootLevel + (Up ? 1 : -1), 0, ShootInfoLevels.Num()-1);

	if (NewLevel == CurrentShootLevel) return false;

	CurrentShootLevel = NewLevel;

	MyPawn->ShootComponent->ShootInfos = ShootInfoLevels[CurrentShootLevel].ShootInfos;

	MyPawn->ShootComponent->ShootPeriod = ShootInfoLevels[CurrentShootLevel].ShootPeriod;

	return true;
}



