// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootComponent1.h"
#include "Engine/world.h"
#include "TimerManager.h"


UShootComponent1::UShootComponent1()
	:
	ShootPeriod(1.f)
{

	// ...
}


void UShootComponent1::BeginPlay()
{
	Super::BeginPlay();

	StartShooting();
	
}

void UShootComponent1::Shoot()
{
	

	for (FShootInfo ShootInfo : ShootInfos)
	{

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = GetOwner();
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 

		FVector SpawnLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorRotation().RotateVector(ShootInfo.Offset);

		FRotator SpawnRotation = GetOwner()->GetActorRotation();
		SpawnRotation.Add(0.f, ShootInfo.Angle, 0.f);

		AShootProjectile* Projectile = GetWorld()->SpawnActor<AShootProjectile>(ShootInfo.ProjectileClass, SpawnLocation, SpawnRotation, SpawnParameters);
		
		if (Projectile) Projectile->Damage = ShootInfo.Damage;

	}
}

void UShootComponent1::StartShooting()
{
	GetWorld()->GetTimerManager().SetTimer(ShootingTimer, this, &UShootComponent1::Shoot, ShootPeriod, true, ShootPeriod);
}

void UShootComponent1::StopShooting()
{
	GetWorld()->GetTimerManager().ClearTimer(ShootingTimer);
}


