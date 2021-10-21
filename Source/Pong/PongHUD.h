// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include <Runtime/Engine/Classes/Engine/TextRenderActor.h>
#include "PongHUD.generated.h"

/**
 * 
 */

UCLASS()
class PONG_API APongHUD : public AHUD
{
	GENERATED_BODY()
private:
	UTextRenderComponent* p1_score_text;
	UTextRenderComponent* p2_score_text;
public:
	APongHUD();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void ChangeP1Score(int32 score);
	virtual void ChangeP2Score(int32 score);
	UFUNCTION()
		void UpdateP1Score();
	UFUNCTION()
		void UpdateP2Score();
	UFUNCTION()
		void GameOverHUD();
	UFUNCTION()
		void ResetScore();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ATextRenderActor> score_text;
};
