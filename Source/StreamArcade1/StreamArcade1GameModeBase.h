// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnemySpawnController.h"
#include "GameHealthComponent.h"
#include "ShootComponent1.h"
#include "StremArcade1GameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);

USTRUCT(BlueprintType)
struct FShootInfoLevel
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		TArray<FShootInfo> ShootInfos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		float ShootPeriod;

};


UCLASS()
class STREMARCADE1_API AStremArcade1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AStremArcade1GameModeBase();

	virtual void BeginPlay() override;

protected:

	UFUNCTION(BlueprintNativeEvent, Category = "Game")
	void ExplodePawn();
	void ExplodePawn_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Game")
	void RecoverPawn();
	void RecoverPawn_Implementation();

	FTimerHandle RecoverTimer;
	FTimerHandle IncreaseDifficultyTimer;

	bool IsGameOver;

public:
		UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Enemies")
		UEnemySpawnController* EnemySpawnController;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Health")
		UGameHealthComponent* HealthsComponent;

		UPROPERTY(BlueprintAssignable, Category = "Game")
		FGameOverEvent GameOver;

		UFUNCTION(BlueprintCallable, Category = "Game")
		void EndGame();

		UFUNCTION(BlueprintCallable, Category = "Game")
		void IncreaseDifficulty();

		UFUNCTION(BlueprintCallable, Category = "Game")
		void AddPoints(int Points);

		UFUNCTION(BlueprintCallable, Category = "Game")
		bool ChangeShootLevel(bool Up);

		UPROPERTY(BlueprintReadWrite, Category = "Game")
		float PlayerRecoverTime;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
		float IncreaseDifficultyPeriod;

		UPROPERTY(BlueprintReadOnly, Category = "Game")
		class AMyPawn* MyPawn;

		UPROPERTY(BlueprintReadOnly, Category = "Game")
		int GamePoints;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shooting")
		TArray<FShootInfoLevel> ShootInfoLevels;
		
		UPROPERTY(BlueprintReadOnly, Category = "Shooting")
		int CurrentShootLevel;

};
