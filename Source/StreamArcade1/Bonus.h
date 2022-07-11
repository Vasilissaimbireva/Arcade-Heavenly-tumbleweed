// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bonus.generated.h"

UCLASS(Blueprintable)
class STREMARCADE1_API ABonus : public AActor
{
	GENERATED_BODY()
	
public:	

	ABonus();

protected:

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override; 
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNAtiveEvent)
	void BonusCollected(); 
	virtual void BonusCollected_Implementation();


public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bonus")
	class USphereComponent* Collision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	UParticleSystem* CollectParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	USoundBase* CollectSound;
};
