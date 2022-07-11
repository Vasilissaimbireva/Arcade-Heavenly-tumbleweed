// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Sound/SoundBase.h"
#include "TimerManager.h"


AMyPawn::AMyPawn()
	:
	MoveLimit(FVector2D(500.f,600.f)),
	TouchMoveSensivity(1.f)
{
 	
	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	RootComponent = PawnCollision;

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(PawnCollision, NAME_None);

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	
	ShootComponent = CreateDefaultSubobject<UShootComponent1>(TEXT("ShootComponent"));

}

void AMyPawn::PossessedBy(AController* NewController)
{
	PlayerController = Cast<APlayerController>(NewController);

}

bool AMyPawn::CanBeDamaged_Implementation()
{
	
	return bCanBeInCluster;

}


void AMyPawn::ExplodePawn_Implementation() 
{
	SetActorEnableCollision(false);

	ShootComponent->StopShooting();

	PawnMesh->SetMaterial(0, RecoverMaterial);

	if (DestroyParticle)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);

	if (CollectSound)
		UGameplayStatics::SpawnSound2D(GetWorld(), CollectSound, 3.0f, 1.0f, 0.0f, (USoundConcurrency*) nullptr, true);

	for (UActorComponent* Component : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
	{
		Component->Deactivate();
	}

}

void AMyPawn::RecoverPawn_Implementation()
{
	SetActorEnableCollision(true);

	ShootComponent->StartShooting();

	PawnMesh->SetMaterial(0, PawnMaterial);


	for (UActorComponent* Component : GetComponentsByClass(UParticleSystemComponent::StaticClass()))
	{
		Component->Activate(true);
	}
}


void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	PawnMaterial = PawnMesh->GetMaterial(0);

	
}

 
float AMyPawn::TakeDamage(float Damage, const  FDamageEvent& DamageEvent, AController* InstigatedBy, AActor* DamageCauser)
{
		
		Super::TakeDamage(Damage, DamageEvent, InstigatedBy, DamageCauser);
		PawnDamaged.Broadcast();
		return Damage;
	
}


void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindTouch(IE_Pressed, this, &AMyPawn::OnTouchPress);

	InputComponent->BindTouch(IE_Repeat, this, &AMyPawn::OnTouchMove);
}

 

void AMyPawn::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{
	FVector2D TouchDeltaMove = FVector2D(TouchLocation.X - Location.X, TouchLocation.Y - Location.Y);

	TouchDeltaMove = TouchDeltaMove * TouchMoveSensivity;

	FVector NewLocation = GetActorLocation();
	NewLocation.X = FMath::Clamp(NewLocation.X + TouchDeltaMove.Y, -MoveLimit.Y, MoveLimit.Y);
	NewLocation.Y = FMath::Clamp(NewLocation.Y + TouchDeltaMove.X * -1.f, -MoveLimit.X, MoveLimit.X);

	SetActorLocation(NewLocation);

	TouchLocation = FVector2D(Location.X, Location.Y);
}

void AMyPawn::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
	TouchLocation = FVector2D(Location.X, Location.Y);

}



