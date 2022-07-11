// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHealthComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"


UGameHealthComponent::UGameHealthComponent()
	:
	Healths(3)
{
}

void UGameHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	
	if (!MyPawn)
	{
		return;
	}
}


void UGameHealthComponent::ChangeHealths(int ByValue)
{
	Healths += ByValue;

	HealthsChanged.Broadcast(ByValue);
	if (Healths <= 0)
	{
		HealthsEnded.Broadcast();
	}
}

int UGameHealthComponent::GetHealths()
{
	return Healths;
}

