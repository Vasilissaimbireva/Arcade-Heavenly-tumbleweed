// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "GameFramework/Actor.h"


UHealthComponent::UHealthComponent()
	: 
	Health(100)
{
	
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnOwnerDamage);
	
}

void UHealthComponent::OnOwnerDamage(AActor * DamagedActor, float Damage, const UDamageType* DamageType, AController* execOnRep_Instigator, AActor* DamageCauser)
{
	ChangeHealth(-Damage);
}



void UHealthComponent::ChangeHealth(float Value)
{
	Health += Value;
	if (Health <= 0.f)
	{
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::OnOwnerDamage);
	
		OnHealthEnded.Broadcast();
	}
}

float UHealthComponent::GetHealth()
{
	return Health;
}



