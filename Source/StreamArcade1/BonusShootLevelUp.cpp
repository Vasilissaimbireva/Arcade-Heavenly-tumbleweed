// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusShootLevelUp.h"
#include "Kismet/GameplayStatics.h"
#include "StremArcade1GameModeBase.h"

void ABonusShootLevelUp::BonusCollected_Implementation()
{
	AStremArcade1GameModeBase* GameMode = Cast<AStremArcade1GameModeBase>(UGameplayStatics::GetGameMode(this));
	if (!GameMode) return;
	
	GameMode->ChangeShootLevel(true);

	Super::BonusCollected_Implementation();

}
