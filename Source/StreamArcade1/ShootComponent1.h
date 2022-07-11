// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootProjectile.h"
#include "ShootComponent1.generated.h"


USTRUCT(BlueprintType)
struct FShootInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TSubclassOf<AShootProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float Damage; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	FVector Offset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float Angle;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STREMARCADE1_API UShootComponent1 : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UShootComponent1();

protected:
	
	virtual void BeginPlay() override;

	void Shoot();

	FTimerHandle ShootingTimer;

public:	

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void StartShooting();

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void StopShooting();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
	float ShootPeriod;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shooting")
	TArray<FShootInfo> ShootInfos;
};

