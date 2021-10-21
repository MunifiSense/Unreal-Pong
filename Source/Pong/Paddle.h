// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Ball.h"
#include "Paddle.generated.h"

UCLASS()
class PONG_API APaddle : public APawn
{
	GENERATED_BODY()

private:
	ABall* ball;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this pawn's properties
	APaddle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool is_ai;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float movement_multiplier;

	//Camera Actor which the Actor Volume blends to
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> main_camera;

	UFUNCTION()
		void PausePaddle();
	UFUNCTION()
		void StartPaddle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
