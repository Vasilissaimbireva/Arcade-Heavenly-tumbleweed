// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusPoints.h"
#include "Kismet/GameplayStatics.h"
#include "StremArcade1GameModeBase.h"

void ABonusPoints::BonusCollected_Implementation()
{
	AStremArcade1GameModeBase* GameMode = Cast<AStremArcade1GameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GameMode) GameMode->AddPoints(Points);

	Super::BonusCollected_Implementation();
	
}

