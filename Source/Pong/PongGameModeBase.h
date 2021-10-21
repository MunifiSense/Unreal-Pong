// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameModeBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FP1Scored);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FP2Scored);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOver);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRestartGame);

UCLASS()
class PONG_API APongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	APongGameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 win_score;
	// Get Player 1 Score
	UFUNCTION(BlueprintPure, Category="Score")
		virtual int32 GetP1Score() const;
	// Get Player 2 Score
	UFUNCTION(BlueprintPure, Category = "Score")
		virtual int32 GetP2Score() const;
	// Set Player 1 Score
	UFUNCTION(BlueprintCallable, Category = "Score")
		virtual void AddP1Score();
	// Set Player 2 Score
	UFUNCTION(BlueprintCallable, Category = "Score")
		virtual void AddP2Score();
	// Reset Scores
	UFUNCTION(BlueprintCallable, Category = "Score")
		virtual void ResetScores();

	UPROPERTY(BlueprintAssignable, Category = "Test")
		FP1Scored OnP1Scored;
	UPROPERTY(BlueprintAssignable, Category = "Test")
		FP2Scored OnP2Scored;
	UPROPERTY(BlueprintAssignable, Category = "Test")
		FGameOver OnGameOver;
	UPROPERTY(BlueprintAssignable, Category = "Test")
		FRestartGame OnRestartGame;

	virtual void StartPlay() override;

};
