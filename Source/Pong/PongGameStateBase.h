// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PongGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APongGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	APongGameStateBase();
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 p1_score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 p2_score;
};
