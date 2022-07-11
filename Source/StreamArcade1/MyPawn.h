// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "ShootComponent1.h"
#include "GameFramework/Actor.h"
#include "MyPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnDamagedEvent);

UCLASS()
class STREMARCADE1_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:

	AMyPawn();



protected:

	virtual void BeginPlay() override;
	
	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* InstigatedBy, AActor* DamageCauser) override;

	void OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location);

	void OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location);

	virtual void PossessedBy(AController* NewController) override;


	APlayerController* PlayerController;

	FVector2D MoveLimit;


private:

	FVector2D TouchLocation;

	bool Touching;
	UMaterialInterface* PawnMaterial;


public:
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent, Category = "Healths")
	bool CanBeDamaged();
	bool CanBeDamaged_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Healths")
	void ExplodePawn();
	void ExplodePawn_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Healths")
	void RecoverPawn();
	void RecoverPawn_Implementation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn")
	UBoxComponent* PawnCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	UStaticMeshComponent* PawnMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	UCameraComponent* PawnCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
	UShootComponent1* ShootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls")
	float TouchMoveSensivity;

	UPROPERTY(BlueprintAssignable, Category = "Healths")
	FPawnDamagedEvent PawnDamaged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
	UMaterialInterface* RecoverMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	UParticleSystem* DestroyParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	USoundBase* CollectSound;
};