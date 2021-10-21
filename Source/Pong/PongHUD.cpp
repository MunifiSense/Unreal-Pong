// Fill out your copyright notice in the Description page of Project Settings.


#include "PongHUD.h"
#include "PongGameModeBase.h"
#include "PongGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include <Runtime/Engine/Classes/Components/TextRenderComponent.h>

APongHUD::APongHUD() {
	
	
}

void APongHUD::BeginPlay() {
	//Array to contain found Text Actors
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), score_text, FoundActors);
	
	p1_score_text = Cast<UTextRenderComponent>(FoundActors[0]->GetRootComponent());
	p2_score_text = Cast<UTextRenderComponent>(FoundActors[1]->GetRootComponent());

	Cast<APongGameModeBase>(GetWorld()->GetAuthGameMode())->OnP1Scored.AddDynamic(this, &APongHUD::UpdateP1Score);
	Cast<APongGameModeBase>(GetWorld()->GetAuthGameMode())->OnP2Scored.AddDynamic(this, &APongHUD::UpdateP2Score);
	Cast<APongGameModeBase>(GetWorld()->GetAuthGameMode())->OnRestartGame.AddDynamic(this, &APongHUD::ResetScore);

	APlayerController* const player_controller = GetWorld()->GetFirstPlayerController();
	if (player_controller) {
		
	}

	Super::BeginPlay();
}

void APongHUD::Tick(float DeltaTime) {
}

void APongHUD::ChangeP1Score(int32 score) {
	p1_score_text->SetText(FText::FromString(FString::FromInt(score)));
}

void APongHUD::ChangeP2Score(int32 score) {
	p2_score_text->SetText(FText::FromString(FString::FromInt(score)));
}

void APongHUD::UpdateP1Score() {
	ChangeP1Score(GetWorld()->GetAuthGameMode()->GetGameState<APongGameStateBase>()->p1_score);
}

void APongHUD::UpdateP2Score() {
	ChangeP2Score(GetWorld()->GetAuthGameMode()->GetGameState<APongGameStateBase>()->p2_score);
}

void APongHUD::GameOverHUD() {
}



void APongHUD::ResetScore() {
	ChangeP1Score(0);
	ChangeP2Score(0);
}






