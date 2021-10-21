// Copyright Epic Games, Inc. All Rights Reserved.


#include "PongGameModeBase.h"
#include "PongGameStateBase.h"
#include "Kismet/GameplayStatics.h"

APongGameModeBase::APongGameModeBase() {
	win_score = 5;
}

int APongGameModeBase::GetP1Score() const {
	return GetGameState<APongGameStateBase>()->p1_score;
}

int APongGameModeBase::GetP2Score() const {
	return GetGameState<APongGameStateBase>()->p2_score;
}

void APongGameModeBase::AddP1Score() {
	GetGameState<APongGameStateBase>()->p1_score++;
	OnP1Scored.Broadcast();

	if (GetGameState<APongGameStateBase>()->p1_score >= win_score) {
		OnGameOver.Broadcast();
	}
}

void APongGameModeBase::AddP2Score() {
	GetGameState<APongGameStateBase>()->p2_score++;
	OnP2Scored.Broadcast();

	if (GetGameState<APongGameStateBase>()->p2_score >= win_score) {
		OnGameOver.Broadcast();
	}
}

void APongGameModeBase::ResetScores() {
	GetGameState<APongGameStateBase>()->p1_score = 0;
	GetGameState<APongGameStateBase>()->p2_score = 0;
	OnRestartGame.Broadcast();
}

void APongGameModeBase::StartPlay() {

	AGameModeBase::StartPlay();
}

