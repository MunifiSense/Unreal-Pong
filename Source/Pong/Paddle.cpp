// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"
#include "PongGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APaddle::APaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	movement_multiplier = 100000.0;
	is_ai = false;
}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	Cast<APongGameModeBase>(GetWorld()->GetAuthGameMode())->OnGameOver.AddDynamic(this, &APaddle::PausePaddle);
	Cast<APongGameModeBase>(GetWorld()->GetAuthGameMode())->OnRestartGame.AddDynamic(this, &APaddle::StartPaddle);

	if (!is_ai) {
		//Array to contain found Camera Actors
		
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), main_camera, FoundActors);
		APlayerController* const player_controller = GetWorld()->GetFirstPlayerController();
		if (player_controller) {
			player_controller->SetViewTargetWithBlend(FoundActors[0]);
		}
	}
	
	//Array to contain found Ball Actors
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Ball"), FoundActors);
	ball = Cast<ABall>(FoundActors[0]);
}

void APaddle::PausePaddle() {
	SetActorTickEnabled(false);
}

void APaddle::StartPaddle() {
	SetActorTickEnabled(true);
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector position = FVector(0, 0, 0);
	if (RootComponent) {
		position = GetActorLocation();
	}

	if (is_ai) {
		if (RootComponent && RootComponent->IsAnySimulatingPhysics()) {
			FVector ball_position = ball->GetRootComponent()->GetComponentLocation();
			if (ball_position.Y > position.Y) {
				Cast<UPrimitiveComponent>(RootComponent)->AddForce(FVector(0.0, 0.5 * movement_multiplier, 0.0));
			}
			else if (ball_position.Y < position.Y) {
				Cast<UPrimitiveComponent>(RootComponent)->AddForce(FVector(0.0, -0.5 * movement_multiplier, 0.0));
			}
		}
	}
	else {
		if (RootComponent && RootComponent->IsAnySimulatingPhysics()) {
			float axis_value = InputComponent->GetAxisValue(TEXT("P1_MoveUp"));
			Cast<UPrimitiveComponent>(RootComponent)->AddForce(FVector(0.0, -axis_value * movement_multiplier, 0.0));
		}
	}

	if (position.Y < -165) {
		Cast<UPrimitiveComponent>(RootComponent)->SetWorldLocation(FVector(position.X, -165.0, position.Z));
	}
	else if (position.Y > 165) {
		Cast<UPrimitiveComponent>(RootComponent)->SetWorldLocation(FVector(position.X, 165.0, position.Z));
	}
}

// Called to bind functionality to input
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (!is_ai) {
		Super::SetupPlayerInputComponent(PlayerInputComponent);
		InputComponent->BindAxis(TEXT("P1_MoveUp"));
	}

}

